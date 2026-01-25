/* Copyright (c) 2013-2018 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
// 包含GUI运行器、音频、核心模拟器、输入和视频相关的头文件
#include "feature/gui/gui-runner.h"
#include <mgba/core/blip_buf.h>
#include <mgba/core/core.h>
#include <mgba/internal/gb/video.h>
#include <mgba/internal/gba/audio.h>
#include <mgba/internal/gba/input.h>
#include <mgba-util/gui.h>
#include <mgba-util/gui/font.h>
#include <mgba-util/gui/menu.h>
#include <mgba-util/vfs.h>

// 包含Switch操作系统和EGL/OpenGL相关的头文件
#include <switch.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>

#include <beiklive/beiklive.h>
struct mGUIRunner* bk_global_runner = NULL;

// 定义自动输入的特殊ID值
#define AUTO_INPUT 0x4E585031
// 音频采样缓冲大小（512个样本）
#define SAMPLES 0x200
// 音频缓冲区数量
#define N_BUFFERS 4
// 模拟摇杆的死区阈值（用于避免输入漂移）
#define ANALOG_DEADZONE 0x4000

// 根据样本数计算缓冲区大小（最小0x1000字节）
#if (SAMPLES * 4) < 0x1000
#define BUFFER_SIZE 0x1000
#else
#define BUFFER_SIZE (SAMPLES * 4)
#endif

// 设置Switch使用用户系统时钟
TimeType __nx_time_type = TimeType_UserSystemClock;

// EGL（OpenGL绑定）相关的全局变量
static EGLDisplay s_display;       // EGL显示器
static EGLContext s_context;       // OpenGL上下文
static EGLSurface s_surface;       // 渲染表面

// 定义四边形顶点的偏移坐标（0-1范围）
static const GLfloat _offsets[] = {
	0.f, 0.f,  // 左下角
	1.f, 0.f,  // 右下角
	1.f, 1.f,  // 右上角
	0.f, 1.f,  // 左上角
};

// OpenGL ES 2.0着色器头部（版本和精度声明）
static const GLchar* const _gles2Header =
	"#version 100\n"
	"precision mediump float;\n";

// 顶点着色器：处理顶点位置和纹理坐标变换
static const char* const _vertexShader =
	"attribute vec2 offset;\n"     // 顶点偏移
	"uniform vec2 dims;\n"         // 缩放尺寸
	"uniform vec2 insize;\n"       // 输入大小
	"varying vec2 texCoord;\n"     // 输出纹理坐标

	"void main() {\n"
	// 计算实际缩放偏移
	"	vec2 ratio = insize;\n"
	"	vec2 scaledOffset = offset * dims;\n"
	// 转换为标准化设备坐标（-1到1）
	"	gl_Position = vec4(scaledOffset.x * 2.0 - dims.x, scaledOffset.y * -2.0 + dims.y, 0.0, 1.0);\n"
	// 计算纹理坐标
	"	texCoord = offset * ratio;\n"
	"}";

// 片段着色器：计算最终像素颜色
static const char* const _fragmentShader =
	"varying vec2 texCoord;\n"     // 纹理坐标
	"uniform sampler2D tex;\n"     // 游戏画面纹理
	"uniform vec4 color;\n"        // 颜色调制

	"void main() {\n"
	// 从纹理采样并转换为RGB
	"	vec4 texColor = vec4(texture2D(tex, texCoord).rgb, 1.0);\n"
	// 应用颜色调制
	"	texColor *= color;\n"
	"	gl_FragColor = texColor;\n"
	"}";

// OpenGL相关的全局变量
static GLuint program;             // 着色器程序
static GLuint vbo;                 // 顶点缓冲对象
static GLuint vao;                 // 顶点数组对象
static GLuint pbo;                 // 像素缓冲对象（用于快速数据传输）
static GLuint copyFbo;             // 帧缓冲对象（用于逐帧混合）
static GLuint texLocation;         // 纹理uniform位置
static GLuint dimsLocation;        // 尺寸uniform位置
static GLuint insizeLocation;      // 输入大小uniform位置
static GLuint colorLocation;       // 颜色uniform位置
static GLuint tex;                 // 当前游戏画面纹理
static GLuint oldTex;              // 前一帧的游戏画面纹理（用于帧混合）



// GUI和游戏相关的全局变量
static struct GUIFont* font;       // GUI字体对象
static color_t* frameBuffer;       // 游戏画面帧缓冲
static struct mAVStream stream;    // 音视频流接口
static struct mSwitchRumble {
	struct mRumble d;              // 振动接口
	int up;                        // 振动增加值
	int down;                      // 振动减少值
	HidVibrationValue value;       // 实际振动强度
} rumble;
static struct mRotationSource rotation = {0}; // 陀螺仪/加速度传感器数据
static int audioBufferActive;                  // 当前活跃的音频缓冲索引
static AudioOutBuffer audoutBuffer[N_BUFFERS]; // 音频输出缓冲
static int enqueuedBuffers;                    // 已入队的音频缓冲数量
static bool frameLimiter = true;               // 是否启用帧率限制
static unsigned framecount = 0;                // 当前帧计数
static unsigned framecap = 10;                 // 最大帧数上限
static PadState pad;                           // 手柄输入状态
static HidSixAxisSensorHandle sixaxisHandles[4]; // 陀螺仪传感器句柄
static HidVibrationDeviceHandle vibrationDeviceHandles[4]; // 振动设备句柄
static HidVibrationValue vibrationStop = { .freq_low = 160.f, .freq_high = 320.f }; // 停止振动值
static bool usePbo = true;         // 是否使用像素缓冲对象
static u8 vmode;                   // 当前显示模式（掌机/底座模式）
static u32 vwidth;                 // 视口宽度
static u32 vheight;                // 视口高度
static bool interframeBlending = false; // 是否启用帧间混合
static bool sgbCrop = false;       // 是否裁剪SGB边框
static bool useLightSensor = true; // 是否使用光传感器
static struct mGUIRunnerLux lightSensor; // 光传感器数据
static float gyroZ = 0;            // 陀螺仪Z轴旋转速度
static float tiltX = 0;            // X轴倾斜加速度
static float tiltY = 0;            // Y轴倾斜加速度

// 音频缓冲池（4个缓冲，每个大小为BUFFER_SIZE字节，4096字节对齐）
static struct mStereoSample audioBuffer[N_BUFFERS][BUFFER_SIZE / 4] __attribute__((__aligned__(0x1000)));

// 屏幕显示模式枚举
static enum ScreenMode {
	SM_PA,    // 像素精确模式（不缩放）
	SM_AF,    // 宽高比适应模式（保持宽高比）
	SM_SF,    // 拉伸填满模式
	SM_MAX    // 模式最大值
} screenMode = SM_PA;

// 纹理过滤模式枚举
static enum FilterMode {
	FM_NEAREST, // 最近邻过滤（最快，但画质差）
	FM_LINEAR,  // 线性过滤（更光滑）
	FM_MAX      // 模式最大值
} filterMode = FM_NEAREST;

// 初始化EGL（OpenGL上下文）
static bool eglInit() {
	// 获取默认EGL显示器
	s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (!s_display) {
		goto _fail0;
	}

	// 初始化EGL
	eglInitialize(s_display, NULL, NULL);

	// 选择EGL配置
	EGLConfig config;
	EGLint numConfigs;
	static const EGLint attributeList[] = {
		EGL_RED_SIZE, 8,    // 红色通道8位
		EGL_GREEN_SIZE, 8,  // 绿色通道8位
		EGL_BLUE_SIZE, 8,   // 蓝色通道8位
		EGL_NONE
	};
	eglChooseConfig(s_display, attributeList, &config, 1, &numConfigs);
	if (!numConfigs) {
		goto _fail1;
	}

	// 创建EGL渲染表面
	s_surface = eglCreateWindowSurface(s_display, config, nwindowGetDefault(), NULL);
	if (!s_surface) {
		goto _fail1;
	}

	// 创建OpenGL ES 3.1上下文
	EGLint contextAttributeList[] = {
		EGL_CONTEXT_MAJOR_VERSION, 3,  // 主版本号
		EGL_CONTEXT_MINOR_VERSION, 1,  // 次版本号
		EGL_NONE
	};
	s_context = eglCreateContext(s_display, config, EGL_NO_CONTEXT, contextAttributeList);
	if (!s_context) {
		goto _fail2;
	}

	// 激活上下文
	eglMakeCurrent(s_display, s_surface, s_surface, s_context);
	return true;

_fail2:
	eglDestroySurface(s_display, s_surface);
	s_surface = NULL;
_fail1:
	eglTerminate(s_display);
	s_display = NULL;
_fail0:
	return false;
}

// 清理EGL资源
static void eglDeinit() {
	if (s_display) {
		// 解除当前上下文
		eglMakeCurrent(s_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		if (s_context) {
			eglDestroyContext(s_display, s_context);
		}
		if (s_surface) {
			eglDestroySurface(s_display, s_surface);
		}
		eglTerminate(s_display);
	}
}

// 映射手柄按键到模拟器输入
static void _mapKey(struct mInputMap* map, uint32_t binding, int nativeKey, int key) {
	// 使用内置函数获取按位位置，绑定按键到输入映射
	mInputBindKey(map, binding, __builtin_ctz(nativeKey), key);
}

// 开始绘制新的一帧
static void _drawStart(void) {
	// 设置清空颜色为黑色
	glClearColor(235.0f/255.0f, 235.0f/255.0f, 235.0f/255.0f, 1.0f);
	// 清空颜色缓冲
	glClear(GL_COLOR_BUFFER_BIT);
}

// 结束绘制并呈现到屏幕
static void _drawEnd(void) {
	// 如果启用帧率限制或超过帧数限制
	if (frameLimiter || framecount >= framecap) {
		// 交换前后缓冲（呈现画面）
		eglSwapBuffers(s_display, s_surface);
		framecount = 0; // 重置计数
	}
}

// 轮询手柄输入
static uint32_t _pollInput(const struct mInputMap* map) {
	int keys = 0;
	// 更新手柄状态
	padUpdate(&pad);
	u32 padkeys = padGetButtons(&pad);
	// 获取映射的按键位
	keys |= mInputMapKeyBits(map, AUTO_INPUT, padkeys, 0);

	// 获取左摇杆位置
	HidAnalogStickState jspos = padGetStickPos(&pad, 0);

	// 尝试从摇杆或方向键获取输入方向
	int l = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_StickLLeft));
	int r = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_StickLRight));
	int u = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_StickLUp));
	int d = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_StickLDown));

	// 如果摇杆方向未映射，使用方向键
	if (l == -1) {
		l = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_Left));
	}
	if (r == -1) {
		r = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_Right));
	}
	if (u == -1) {
		u = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_Up));
	}
	if (d == -1) {
		d = mInputMapKey(map, AUTO_INPUT, __builtin_ctz(HidNpadButton_Down));
	}

	// 处理摇杆输入（超过死区阈值）
	if (jspos.x < -ANALOG_DEADZONE && l != -1) {
		keys |= 1 << l;  // 左移
	}
	if (jspos.x > ANALOG_DEADZONE && r != -1) {
		keys |= 1 << r;  // 右移
	}
	if (jspos.y < -ANALOG_DEADZONE && d != -1) {
		keys |= 1 << d;  // 下移
	}
	if (jspos.y > ANALOG_DEADZONE && u != -1) {
		keys |= 1 << u;  // 上移
	}
	return keys;
}

// 轮询触摸屏输入
static enum GUICursorState _pollCursor(unsigned* x, unsigned* y) {
	HidTouchScreenState state = {0};
	// 获取触摸屏状态
	hidGetTouchScreenStates(&state, 1);
	if (state.count < 1) {
		return GUI_CURSOR_NOT_PRESENT;
	}
	// 返回触摸位置
	*x = state.touches[0].x;
	*y = state.touches[0].y;
	return GUI_CURSOR_DOWN;
}

// 更新渲染器模式（GPU加速或软件渲染）
static void _updateRenderer(struct mGUIRunner* runner, bool gl) {
	if (gl) {
		// GPU加速模式：使用OpenGL纹理渲染
		runner->core->setVideoGLTex(runner->core, tex);
		usePbo = false;
	} else {
		// 软件渲染模式：准备纹理并设置帧缓冲
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		runner->core->setVideoBuffer(runner->core, frameBuffer, 256);
		usePbo = true;
	}
}

// 等待音频播放完成或获取已释放的音频缓冲
static int _audioWait(u64 timeout) {
	AudioOutBuffer* releasedBuffers;
	u32 nReleasedBuffers = 0;
	Result rc;
	if (timeout) {
		// 等待指定时间直到音频播放完成
		rc = audoutWaitPlayFinish(&releasedBuffers, &nReleasedBuffers, timeout);
	} else {
		// 非阻塞地获取已释放的缓冲
		rc = audoutGetReleasedAudioOutBuffer(&releasedBuffers, &nReleasedBuffers);
	}
	if (R_FAILED(rc)) {
		return 0;
	}
	// 减少已入队的缓冲计数
	enqueuedBuffers -= nReleasedBuffers;
	return nReleasedBuffers;
}

// 设置游戏控制器按键映射
static void _setup(struct mGUIRunner* runner) {
	// 映射Switch手柄按键到GBA按键
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_A, GBA_KEY_A);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_B, GBA_KEY_B);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_Plus, GBA_KEY_START);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_Minus, GBA_KEY_SELECT);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_Up, GBA_KEY_UP);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_Down, GBA_KEY_DOWN);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_Left, GBA_KEY_LEFT);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_Right, GBA_KEY_RIGHT);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_L, GBA_KEY_L);
	_mapKey(&runner->core->inputMap, AUTO_INPUT, HidNpadButton_R, GBA_KEY_R);

	// 检查是否支持GPU加速
	int fakeBool = false;
	if (runner->core->supportsFeature(runner->core, mCORE_FEATURE_OPENGL)) {
		mCoreConfigGetIntValue(&runner->config, "hwaccelVideo", &fakeBool);
	}
	_updateRenderer(runner, fakeBool);

	// 设置外设（振动、陀螺仪等）
	runner->core->setPeripheral(runner->core, mPERIPH_RUMBLE, &rumble.d);
	runner->core->setPeripheral(runner->core, mPERIPH_ROTATION, &rotation);
	runner->core->setAVStream(runner->core, &stream);

	// 如果是GBA游戏且支持光传感器
	if (runner->core->platform(runner->core) == mPLATFORM_GBA && useLightSensor) {
		runner->core->setPeripheral(runner->core, mPERIPH_GBA_LUMINANCE, &lightSensor.d);
	}

	// 读取配置（屏幕模式、过滤模式）
	unsigned mode;
	if (mCoreConfigGetUIntValue(&runner->config, "screenMode", &mode) && mode < SM_MAX) {
		screenMode = mode;
	}
	if (mCoreConfigGetUIntValue(&runner->config, "filterMode", &mode) && mode < FM_MAX) {
		filterMode = mode;
	}

	// 设置音频缓冲大小
	runner->core->setAudioBufferSize(runner->core, SAMPLES);
}

// 游戏加载完成后的初始化
static void _gameLoaded(struct mGUIRunner* runner) {
	// 获取音频采样率
	u32 samplerate = audoutGetSampleRate();

	// 计算音频比例并配置混音库
	double ratio = GBAAudioCalculateRatio(1, 60.0, 1);
	blip_set_rates(runner->core->getAudioChannel(runner->core, 0), runner->core->frequency(runner->core), samplerate * ratio);
	blip_set_rates(runner->core->getAudioChannel(runner->core, 1), runner->core->frequency(runner->core), samplerate * ratio);

	// 读取快进帧数上限
	mCoreConfigGetUIntValue(&runner->config, "fastForwardCap", &framecap);

	unsigned mode;
	if (mCoreConfigGetUIntValue(&runner->config, "screenMode", &mode) && mode < SM_MAX) {
		screenMode = mode;
	}
	if (mCoreConfigGetUIntValue(&runner->config, "filterMode", &mode) && mode < FM_MAX) {
		filterMode = mode;
	}

	// 读取游戏配置选项
	int fakeBool;
	if (mCoreConfigGetIntValue(&runner->config, "interframeBlending", &fakeBool)) {
		interframeBlending = fakeBool;  // 帧间混合
	}
	if (mCoreConfigGetIntValue(&runner->config, "sgb.borderCrop", &fakeBool)) {
		sgbCrop = fakeBool;             // SGB边框裁剪
	}
	if (mCoreConfigGetIntValue(&runner->config, "useLightSensor", &fakeBool)) {
		if (useLightSensor != fakeBool) {
			useLightSensor = fakeBool;

			// 根据配置切换光传感器
			if (runner->core->platform(runner->core) == mPLATFORM_GBA) {
				if (useLightSensor) {
					runner->core->setPeripheral(runner->core, mPERIPH_GBA_LUMINANCE, &lightSensor.d);
				} else {
					runner->core->setPeripheral(runner->core, mPERIPH_GBA_LUMINANCE, &runner->luminanceSource.d);
				}
			}
		}
	}

	// 处理GPU加速配置更改
	if (runner->core->supportsFeature(runner->core, mCORE_FEATURE_OPENGL)) {
		if (mCoreConfigGetIntValue(&runner->config, "hwaccelVideo", &fakeBool) && fakeBool == usePbo) {
			_updateRenderer(runner, fakeBool);
			runner->core->reloadConfigOption(runner->core, "hwaccelVideo", &runner->config);
		}

		unsigned scale;
		if (mCoreConfigGetUIntValue(&runner->config, "videoScale", &scale)) {
			runner->core->reloadConfigOption(runner->core, "videoScale", &runner->config);
		}
	}

	// 重置振动状态
	rumble.up = 0;
	rumble.down = 0;
}

// 游戏卸载前的清理
static void _gameUnloaded(struct mGUIRunner* runner) {
	// 停止所有振动设备
	HidVibrationValue values[4];
	memcpy(&values[0], &vibrationStop, sizeof(rumble.value));
	memcpy(&values[1], &vibrationStop, sizeof(rumble.value));
	memcpy(&values[2], &vibrationStop, sizeof(rumble.value));
	memcpy(&values[3], &vibrationStop, sizeof(rumble.value));
	hidSendVibrationValues(vibrationDeviceHandles, values, 4);
}
// 将游戏画面纹理绘制到屏幕上的函数
static void _drawTex(
	struct mGUIRunner* runner,   // GUI 运行上下文
	unsigned width,              // 输入纹理宽度（游戏画面宽）
	unsigned height,             // 输入纹理高度（游戏画面高）
	bool faded,                  // 是否启用淡化效果
	bool blendTop                // 是否与上层画面混合
) {
	// 设置 OpenGL 视口
	// (x=0, y=1080-vheight) 表示从屏幕顶部向下绘制
	glViewport(0, 1080 - vheight, vwidth, vheight);

	// 启用 alpha 混合
	glEnable(GL_BLEND);

	// 设置混合方式：标准的 alpha 混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 设置纹理放大时的过滤方式
	// 线性过滤（平滑）或最近邻（像素风）
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		filterMode == FM_LINEAR ? GL_LINEAR : GL_NEAREST
	);

	// 使用当前着色器程序
	glUseProgram(program);

	// 绑定顶点数组对象（包含全屏四边形顶点）
	glBindVertexArray(vao);

	// 保存输入纹理尺寸为浮点数
	float inwidth = width;
	float inheight = height;
	
	// 如果启用了 SGB 裁剪，且当前分辨率是 SGB 标准分辨率
	if (sgbCrop && width == 256 && height == 224) {

		// 使用 Game Boy 实际可视区域尺寸
		inwidth = GB_VIDEO_HORIZONTAL_PIXELS;
		inheight = GB_VIDEO_VERTICAL_PIXELS;
	}
	
	// 计算输入纹理与视口的宽高比例
	float aspectX = inwidth / vwidth;
	float aspectY = inheight / vheight;

	// 最大缩放因子，默认 1（不缩放）
	float max = 1.f;
	
	// 根据屏幕显示模式计算缩放方式
	switch (screenMode) {

	case SM_PA:
		// 像素精确模式（Pixel Accurate）
		// 选择整数倍缩放，避免像素失真
		if (aspectX > aspectY) {
			max = floor(1.f / aspectX);
		} else {
			max = floor(1.f / aspectY);
		}

		// 如果可用缩放倍数 >= 1，直接使用
		if (max >= 1.f) {
			break;
		}
		// 否则继续执行下一个模式
		// Fall through

	case SM_AF:
		// 宽高比适应模式（Aspect Fit）
		// 保持宽高比，画面完整显示
		if (aspectX > aspectY) {
			max = 1.f / aspectX;
		} else {
			max = 1.f / aspectY;
		}
		break;

	case SM_SF:
		// 拉伸填满模式（Stretch Fill）
		// 不保持宽高比，完全填充屏幕
		aspectX = 1.f;
		aspectY = 1.f;
		break;
	}

	// 如果不是拉伸填满模式
	if (screenMode != SM_SF) {

		// 重新基于实际纹理尺寸计算宽高比例
		aspectX = width / (float) vwidth;
		aspectY = height / (float) vheight;
	}

	// 应用最终缩放因子
	aspectX *= max;
	aspectY *= max;

	// 设置纹理采样单元（使用 0 号纹理）
	glUniform1i(texLocation, 0);

	// 设置输出尺寸比例（用于顶点或片段着色器）
	glUniform2f(dimsLocation, aspectX, aspectY);

	// 如果使用 PBO（Pixel Buffer Object）
	if (usePbo) {
		// 设置输入纹理尺寸相对值（通常用于特殊缩放）
		glUniform2f(insizeLocation, width / 256.f, height / 256.f);
	} else {
		// 否则使用默认值
		glUniform2f(insizeLocation, 1, 1);
	}

	// 根据是否淡化来设置颜色和透明度
	if (!faded) {

		// 正常亮度
		glUniform4f(
			colorLocation,
			1.0f, 1.0f, 1.0f,
			blendTop ? 0.5f : 1.0f
		);
	} else {

		// 淡化状态（亮度降低）
		glUniform4f(
			colorLocation,
			0.8f, 0.8f, 0.8f,
			blendTop ? 0.4f : 0.8f
		);
	}

	// 使用三角扇绘制一个矩形（四个顶点）
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	// 解绑顶点数组
	glBindVertexArray(0);

	// 停止使用着色器程序
	glUseProgram(0);

	// 关闭混合
	glDisable(GL_BLEND);

	// 恢复 GUI 原始视口大小
	glViewport(
		0,
		1080 - runner->params.height,
		runner->params.width,
		runner->params.height
	);
}






// BKMARK 自定义背景绘制函数

// 绘制游戏画面纹理到指定位置和大小
static void _drawTexCustom(struct mGUIRunner* runner,
                          unsigned texWidth, unsigned texHeight,
                          bool faded, bool blendTop,
                          int targetX, int targetY,
                          int targetWidth, int targetHeight)
{
    // 计算 OpenGL viewport（基于 vheight，而不是 screenH）
    // 计算视口左下角坐标
	if(targetX < 0) targetX = 0;
	if(targetY < 0) targetY = 0;
	// if(targetX + targetWidth > vwidth) targetWidth = vwidth - targetX;
	// if(targetY + targetHeight > vheight) targetHeight = vheight - targetY;


	
	
	int vpX = targetX;
    int vpY = 1080 - targetY - targetHeight;  
    // glViewport(vpX, vpY, targetWidth, targetHeight);
    glViewport(0, 360, 1280, 720);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		filterMode == FM_LINEAR ? GL_LINEAR : GL_NEAREST
	);

    glUseProgram(program);
    glBindVertexArray(vao);

	// 保存输入纹理尺寸为浮点数
	float inwidth = texWidth;
	float inheight = texHeight;

	// 计算输入纹理与视口的宽高比例
	float aspectX = inwidth / (float) targetWidth;
	float aspectY = inheight / (float) targetHeight;


    // 纹理相关 uniform
    glUniform1i(texLocation, 0);
    glUniform2f(dimsLocation, 1.0f, 1.0f);

	// if (usePbo) {
	// 	// 设置输入纹理尺寸相对值（通常用于特殊缩放）
	// 	glUniform2f(insizeLocation, width / 256.f, height / 256.f);
	// } else {
	// 	// 否则使用默认值
	// 	glUniform2f(insizeLocation, 1, 1);
	// }
	glUniform2f(insizeLocation, 1, 1);


    if (!faded) {
        glUniform4f(colorLocation, 1.0f, 1.0f, 1.0f, blendTop ? 0.5f : 1.0f);
    } else {
        glUniform4f(colorLocation, 0.8f, 0.8f, 0.8f, blendTop ? 0.4f : 0.8f);
    }

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    glUseProgram(0);
    glDisable(GL_BLEND);

    // 恢复主 viewport
    glViewport(
        0,
        1080 - runner->params.height,
        runner->params.width,
        runner->params.height
    );
}



static void _drawBKImage(struct mGUIRunner* runner, const color_t* pixels, 
                                 unsigned width, unsigned height, bool faded,
                                 int targetX, int targetY, 
                                 int targetWidth, int targetHeight, bool isSame) {
    // 上传像素数据到纹理
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, bkTex);
	if(!isSame)		
	{
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, 
			GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	}	

    // 绘制到指定位置和大小
    _drawTexCustom(runner, width, height, faded, false, 
                   targetX, targetY, targetWidth, targetHeight);
}















// 为新帧做准备（处理帧间混合和像素缓冲）
static void _prepareForFrame(struct mGUIRunner* runner) {
	if (interframeBlending) {
		// 复制当前纹理到旧纹理用于混合
		glBindFramebuffer(GL_READ_FRAMEBUFFER, copyFbo);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		int width, height;
		int format;
		glBindTexture(GL_TEXTURE_2D, tex);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);
		glBindTexture(GL_TEXTURE_2D, oldTex);
		glCopyTexImage2D(GL_TEXTURE_2D, 0, format, 0, 0, width, height, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	// 如果使用像素缓冲对象
	if (usePbo) {
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
		// 映射缓冲到CPU内存以供写入
		frameBuffer = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, 256 * 256 * 4, GL_MAP_WRITE_BIT);
		if (frameBuffer) {
			runner->core->setVideoBuffer(runner->core, frameBuffer, 256);
		}
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	}
}

// 绘制游戏画面
static void _drawFrame(struct mGUIRunner* runner, bool faded) {
	++framecount;
	// 如果未启用帧率限制且未达到帧数上限，则跳过绘制
	if (!frameLimiter && framecount < framecap) {
		return;
	}

	// 获取期望的视频尺寸
	unsigned width, height;
	runner->core->desiredVideoDimensions(runner->core, &width, &height);

	glActiveTexture(GL_TEXTURE0);
	if (usePbo) {
		// 上传像素缓冲数据到纹理
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
		glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);

		glBindTexture(GL_TEXTURE_2D, tex);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 256, height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	} else if (!interframeBlending) {
		glBindTexture(GL_TEXTURE_2D, tex);
	}

	// 如果启用帧间混合，先绘制淡化的前一帧，再绘制当前帧
	if (interframeBlending) {
		glBindTexture(GL_TEXTURE_2D, oldTex);
		_drawTex(runner, width, height, faded, false);
		glBindTexture(GL_TEXTURE_2D, tex);
		_drawTex(runner, width, height, faded, true);
	} else {
		_drawTex(runner, width, height, faded, false);
	}

	// 处理振动反馈
	HidVibrationValue values[4];
	if (rumble.up) {
		// 根据振动强度比例设置振动
		rumble.value.amp_low = rumble.up / (float) (rumble.up + rumble.down);
		rumble.value.amp_high = rumble.up / (float) (rumble.up + rumble.down);
		memcpy(&values[0], &rumble.value, sizeof(rumble.value));
		memcpy(&values[1], &rumble.value, sizeof(rumble.value));
		memcpy(&values[2], &rumble.value, sizeof(rumble.value));
		memcpy(&values[3], &rumble.value, sizeof(rumble.value));
	} else {
		// 停止振动
		memcpy(&values[0], &vibrationStop, sizeof(rumble.value));
		memcpy(&values[1], &vibrationStop, sizeof(rumble.value));
		memcpy(&values[2], &vibrationStop, sizeof(rumble.value));
		memcpy(&values[3], &vibrationStop, sizeof(rumble.value));
	}
	hidSendVibrationValues(vibrationDeviceHandles, values, 4);
	rumble.up = 0;
	rumble.down = 0;
}

// 绘制游戏截图
static void _drawScreenshot(struct mGUIRunner* runner, const color_t* pixels, unsigned width, unsigned height, bool faded) {
	// 上传像素数据到纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	// 绘制到屏幕
	_drawTex(runner, width, height, faded, false);
}

// 轮询游戏输入
static uint16_t _pollGameInput(struct mGUIRunner* runner) {
	return _pollInput(&runner->core->inputMap);
}

// 循环切换屏幕显示模式
static void _incrementScreenMode(struct mGUIRunner* runner) {
	UNUSED(runner);
	screenMode = (screenMode + 1) % SM_MAX;
	mCoreConfigSetUIntValue(&runner->config, "screenMode", screenMode);
}

// 设置帧率限制
static void _setFrameLimiter(struct mGUIRunner* runner, bool limit) {
	UNUSED(runner);
	if (!frameLimiter && limit) {
		// 从无限制切换到限制，等待音频缓冲排空
		while (enqueuedBuffers > 2) {
			_audioWait(100000000);
		}
	}
	frameLimiter = limit;
	// 设置EGL交换间隔（0 = 不等待，1 = 等待垂直同步）
	eglSwapInterval(s_surface, limit);
}

// 检查应用是否应继续运行
static bool _running(struct mGUIRunner* runner) {
	UNUSED(runner);
	// 检查是否从掌机模式切换到底座模式
	u8 newMode = appletGetOperationMode();
	if (newMode != vmode) {
		if (newMode == AppletOperationMode_Console) {
			vwidth = 1920;
			vheight = 1080;
		} else {
			vwidth = 1280;
			vheight = 720;
		}
		nwindowSetCrop(nwindowGetDefault(), 0, 0, vwidth, vheight);
		vmode = newMode;
	}

	// 检查应用是否应继续运行
	return appletMainLoop();
}

// 向音频设备输出音频缓冲
static void _postAudioBuffer(struct mAVStream* stream, blip_t* left, blip_t* right) {
	UNUSED(stream);
	// 回收已播放的音频缓冲
	_audioWait(0);
	// 等待缓冲可用
	while (enqueuedBuffers >= N_BUFFERS - 1) {
		if (!frameLimiter) {
			// 如果未启用帧率限制，丢弃音频
			blip_clear(left);
			blip_clear(right);
			return;
		}
		_audioWait(10000000);
	}
	if (enqueuedBuffers >= N_BUFFERS) {
		blip_clear(left);
		blip_clear(right);
		return;
	}
	
	// 读取音频样本到缓冲
	struct mStereoSample* samples = audioBuffer[audioBufferActive];
	blip_read_samples(left, &samples[0].left, SAMPLES, true);
	blip_read_samples(right, &samples[0].right, SAMPLES, true);
	// 提交缓冲给音频系统
	audoutAppendAudioOutBuffer(&audoutBuffer[audioBufferActive]);
	++audioBufferActive;
	audioBufferActive %= N_BUFFERS;
	++enqueuedBuffers;
}

// 设置震动强度
void _setRumble(struct mRumble* rumble, int enable) {
	struct mSwitchRumble* sr = (struct mSwitchRumble*) rumble;
	if (enable) {
		++sr->up;    // 增加上升强度
	} else {
		++sr->down;  // 增加下降强度
	}
}

// 采样陀螺仪和加速度传感器数据
void _sampleRotation(struct mRotationSource* source) {
	HidSixAxisSensorState sixaxis = {0};
	u64 styles = padGetStyleSet(&pad);
	
	// 根据手柄类型获取相应的传感器数据
	if (styles & HidNpadStyleTag_NpadHandheld) {
		hidGetSixAxisSensorStates(sixaxisHandles[3], &sixaxis, 1);
	} else if (styles & HidNpadStyleTag_NpadFullKey) {
		hidGetSixAxisSensorStates(sixaxisHandles[2], &sixaxis, 1);
	} else if (styles & HidNpadStyleTag_NpadJoyDual) {
		u64 attrib = padGetAttributes(&pad);
		if (attrib & HidNpadAttribute_IsLeftConnected) {
			hidGetSixAxisSensorStates(sixaxisHandles[0], &sixaxis, 1);
		} else if (attrib & HidNpadAttribute_IsRightConnected) {
			hidGetSixAxisSensorStates(sixaxisHandles[1], &sixaxis, 1);
		} else {
			return;
		}
	}
	
	// 转换加速度值
	tiltX = sixaxis.acceleration.x * 3e8f;
	tiltY = sixaxis.acceleration.y * -3e8f;
	// 转换角速度值
	gyroZ = sixaxis.angular_velocity.z * -5.5e8f;
}

// 读取X轴倾斜值
int32_t _readTiltX(struct mRotationSource* source) {
	UNUSED(source);
	return tiltX;
}

// 读取Y轴倾斜值
int32_t _readTiltY(struct mRotationSource* source) {
	UNUSED(source);
	return tiltY;
}

// 读取Z轴陀螺仪值
int32_t _readGyroZ(struct mRotationSource* source) {
	UNUSED(source);
	return gyroZ;
}

// 采样光传感器数据
static void _lightSensorSample(struct GBALuminanceSource* lux) {
	struct mGUIRunnerLux* runnerLux = (struct mGUIRunnerLux*) lux;
	float luxLevel = 0;
	// 获取当前照度值
	appletGetCurrentIlluminance(&luxLevel);
	// 计算Lux值（立方根变换）
	runnerLux->luxLevel = cbrtf(luxLevel) * 8;
}

// 读取光传感器值
static uint8_t _lightSensorRead(struct GBALuminanceSource* lux) {
	struct mGUIRunnerLux* runnerLux = (struct mGUIRunnerLux*) lux;
	// 返回反转的亮度值（0xFF - lux）
	return 0xFF - runnerLux->luxLevel;
}

// 获取电池状态
static int _batteryState(void) {
	u32 charge;
	int state = 0;
	// 获取电池百分比
	if (R_SUCCEEDED(psmGetBatteryChargePercentage(&charge))) {
		state = charge | BATTERY_PERCENTAGE_VALID;
	} else {
		return BATTERY_NOT_PRESENT;
	}
	// 检查充电状态
	PsmChargerType type;
	if (R_SUCCEEDED(psmGetChargerType(&type)) && type) {
		state |= BATTERY_CHARGING;
	}
	return state;
}

// GUI绘制前的准备
static void _guiPrepare(void) {
	glViewport(0, 1080 - vheight, vwidth, vheight);
}

// GUI绘制后的提交
static void _guiFinish(void) {
	// 提交所有字体绘制命令到GPU
	GUIFontDrawSubmit(font);
}

// 运行软键盘输入对话框
static enum GUIKeyboardStatus _keyboardRun(struct GUIKeyboardParams* keyboard) {
	SwkbdConfig swkbd;
	swkbdCreate(&swkbd, 0);
	swkbdConfigMakePresetDefault(&swkbd);
	swkbdConfigSetStringLenMax(&swkbd, keyboard->maxLen);
	swkbdConfigSetType(&swkbd, SwkbdType_All);  // 打开中文拼音输入
	swkbdConfigSetInitialText(&swkbd, keyboard->result);
	swkbdConfigSetHeaderText(&swkbd, keyboard->title);
	swkbdConfigSetReturnButtonFlag(&swkbd, keyboard->multiline);

	// 显示软键盘
	Result rc = swkbdShow(&swkbd, keyboard->result, sizeof(keyboard->result));
	swkbdClose(&swkbd);
	if (R_SUCCEEDED(rc)) {
		return GUI_KEYBOARD_DONE;
	} else {
		return GUI_KEYBOARD_CANCEL;
	}
}

// 初始化OpenGL环境
static void glInit(void) {
	glViewport(0, 1080 - vheight, vwidth, vheight);
	glClearColor(0.f, 0.f, 0.f, 1.f);

	// 创建游戏画面纹理
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// 创建前一帧纹理（用于帧混合）
	glGenTextures(1, &oldTex);
	glBindTexture(GL_TEXTURE_2D, oldTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// 创建像素缓冲对象用于快速数据传输
	glGenBuffers(1, &pbo);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, 256 * 256 * 4, NULL, GL_STREAM_DRAW);
	frameBuffer = glMapBufferRange(GL_PIXEL_UNPACK_BUFFER, 0, 256 * 256 * 4, GL_MAP_WRITE_BIT);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

	// 创建帧缓冲对象用于复制操作
	glGenFramebuffers(1, &copyFbo);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, oldTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, copyFbo);
	glFramebufferTexture2D(GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

	// 编译着色器程序
	program = glCreateProgram();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* shaderBuffer[2];

	shaderBuffer[0] = _gles2Header;

	shaderBuffer[1] = _vertexShader;
	glShaderSource(vertexShader, 2, shaderBuffer, NULL);

	shaderBuffer[1] = _fragmentShader;
	glShaderSource(fragmentShader, 2, shaderBuffer, NULL);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// 编译和检查片段着色器
	glCompileShader(fragmentShader);
	GLint success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar msg[512];
		glGetShaderInfoLog(fragmentShader, sizeof(msg), NULL, msg);
		puts(msg);
	}

	// 编译和检查顶点着色器
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar msg[512];
		glGetShaderInfoLog(vertexShader, sizeof(msg), NULL, msg);
		puts(msg);
	}
	
	// 链接程序
	glLinkProgram(program);

	// 删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 获取uniform变量位置
	texLocation = glGetUniformLocation(program, "tex");
	colorLocation = glGetUniformLocation(program, "color");
	dimsLocation = glGetUniformLocation(program, "dims");
	insizeLocation = glGetUniformLocation(program, "insize");
	GLuint offsetLocation = glGetAttribLocation(program, "offset");

	// 创建顶点缓冲和数组对象
	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_offsets), _offsets, GL_STATIC_DRAW);
	glVertexAttribPointer(offsetLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(offsetLocation);
	glBindVertexArray(0);
}

// 清理OpenGL资源
static void glDeinit(void) {
	// 解除像素缓冲映射并删除
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbo);
	glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
	glDeleteBuffers(1, &pbo);

	// 删除所有GPU对象
	glDeleteFramebuffers(1, &copyFbo);
	glDeleteTextures(1, &tex);
	glDeleteTextures(1, &oldTex);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(program);
	glDeleteVertexArrays(1, &vao);
}

// 初始化手柄和传感器
static void hidSetup(void) {
	// 初始化触摸屏
	hidInitializeTouchScreen();
	// 配置手柄输入
	padConfigureInput(1, HidNpadStyleSet_NpadStandard);
	padInitializeDefault(&pad);

	// 设置振动功能
	rumble.d.setRumble = _setRumble;
	rumble.value.freq_low = 120.0;
	rumble.value.freq_high = 180.0;
	hidInitializeVibrationDevices(&vibrationDeviceHandles[0], 2, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
	hidInitializeVibrationDevices(&vibrationDeviceHandles[2], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);

	// 获取陀螺仪传感器句柄
	hidGetSixAxisSensorHandles(&sixaxisHandles[0], 2, HidNpadIdType_No1, HidNpadStyleTag_NpadJoyDual);
	hidGetSixAxisSensorHandles(&sixaxisHandles[2], 1, HidNpadIdType_No1, HidNpadStyleTag_NpadFullKey);
	hidGetSixAxisSensorHandles(&sixaxisHandles[3], 1, HidNpadIdType_Handheld, HidNpadStyleTag_NpadHandheld);
	// 启动所有陀螺仪传感器
	hidStartSixAxisSensor(sixaxisHandles[0]);
	hidStartSixAxisSensor(sixaxisHandles[1]);
	hidStartSixAxisSensor(sixaxisHandles[2]);
	hidStartSixAxisSensor(sixaxisHandles[3]);
	// 设置旋转传感器回调
	rotation.readTiltX = _readTiltX;
	rotation.readTiltY = _readTiltY;
	rotation.readGyroZ = _readGyroZ;
	rotation.sample = _sampleRotation;

	// 设置光传感器回调
	lightSensor.d.readLuminance = _lightSensorRead;
	lightSensor.d.sample = _lightSensorSample;
}

// 清理手柄和传感器
static void hidTeardown(void) {
	// 停止所有陀螺仪传感器
	hidStopSixAxisSensor(sixaxisHandles[0]);
	hidStopSixAxisSensor(sixaxisHandles[1]);
	hidStopSixAxisSensor(sixaxisHandles[2]);
	hidStopSixAxisSensor(sixaxisHandles[3]);
}

// 主函数入口
int main(int argc, char* argv[]) {
	NWindow* window = nwindowGetDefault();
	nwindowSetDimensions(window, 1920, 1080);

	// 初始化各个系统
	socketInitializeDefault();   // 网络套接字
	nxlinkStdio();               // 标准IO重定向
	eglInit();                   // OpenGL上下文
	romfsInit();                 // 只读文件系统
	audoutInitialize();          // 音频输出
	psmInitialize();             // 电源状态管理

	// 创建GUI字体
	font = GUIFontCreate();

	// 初始化显示模式
	vmode = appletGetOperationMode();
	if (vmode == AppletOperationMode_Console) {
		vwidth = 1920;
		vheight = 1080;
	} else {
		vwidth = 1280;
		vheight = 720;
	}
	nwindowSetCrop(window, 0, 0, vwidth, vheight);

	// 初始化OpenGL和手柄
	glInit();

	bk_opengl_init();

	hidSetup();

	// 设置音视频流回调
	stream.videoDimensionsChanged = NULL;
	stream.postVideoFrame = NULL;
	stream.postAudioFrame = NULL;
	stream.postAudioBuffer = _postAudioBuffer;

	// 初始化音频缓冲池
	memset(audioBuffer, 0, sizeof(audioBuffer));
	audioBufferActive = 0;
	enqueuedBuffers = 0;
	size_t i;
	for (i = 0; i < N_BUFFERS; ++i) {
		audoutBuffer[i].next = NULL;
		audoutBuffer[i].buffer = audioBuffer[i];
		audoutBuffer[i].buffer_size = BUFFER_SIZE;
		audoutBuffer[i].data_size = SAMPLES * 4;
		audoutBuffer[i].data_offset = 0;
	}

	// 检查照度传感器是否可用
	bool illuminanceAvailable = false;
	appletIsIlluminanceAvailable(&illuminanceAvailable);

	// 初始化GUI运行器
	struct mGUIRunner runner = {
		.params = {
			1280, 720,
			font, "/",
			_drawStart, _drawEnd,
			_pollInput, _pollCursor,
			_batteryState,
			_guiPrepare, _guiFinish,
			_keyboardRun,
		},
		.keySources = (struct GUIInputKeys[]) {
			{
				.name = "Controller Input",
				.id = AUTO_INPUT,
				.keyNames = (const char*[]) {
					"A",
					"B",
					"X",
					"Y",
					"L Stick",
					"R Stick",
					"L",
					"R",
					"ZL",
					"ZR",
					"+",
					"-",
					"Left",
					"Up",
					"Right",
					"Down",
					"L Left",
					"L Up",
					"L Right",
					"L Down",
					"R Left",
					"R Up",
					"R Right",
					"R Down",
					"SL",
					"SR"
				},
				.nKeys = 26
			},
			{ .id = 0 }
		},
		.configExtra = (struct GUIMenuItem[]) {
			{
				.title = "屏幕模式",
				.data = GUI_V_S("screenMode"),
				.submenu = 0,
				.state = SM_PA,
				.validStates = (const char*[]) {
					"精确像素(Pixel-Accurate)",
					"按比例填充(Aspect-Ratio Fit)",
					"全屏拉伸(Stretched)",
				},
				.nStates = 3
			},
			{
				.title = "加速上限",
				.data = GUI_V_S("fastForwardCap"),
				.submenu = 0,
				.state = 7,
				.validStates = (const char*[]) {
					"2", "3", "4", "5", "6", "7", "8", "9",
					"10", "11", "12", "13", "14", "15",
					"20", "30"
				},
				.stateMappings = (const struct GUIVariant[]) {
					GUI_V_U(2),
					GUI_V_U(3),
					GUI_V_U(4),
					GUI_V_U(5),
					GUI_V_U(6),
					GUI_V_U(7),
					GUI_V_U(8),
					GUI_V_U(9),
					GUI_V_U(10),
					GUI_V_U(11),
					GUI_V_U(12),
					GUI_V_U(13),
					GUI_V_U(14),
					GUI_V_U(15),
					GUI_V_U(20),
					GUI_V_U(30),
				},
				.nStates = 16
			},
			{
				.title = "纹理过滤",
				.data = GUI_V_S("filterMode"),
				.submenu = 0,
				.state = FM_NEAREST,
				.validStates = (const char*[]) {
					"无",
					"双线性(Bilinear)",
				},
				.nStates = 2
			},
			{
				.title = "GPU渲染",
				.data = GUI_V_S("hwaccelVideo"),
				.submenu = 0,
				.state = 0,
				.validStates = (const char*[]) {
					"关闭",
					"打开",
				},
				.nStates = 2
			},
			{
				.title = "高清缩放(需GPU渲染)",
				.data = GUI_V_S("videoScale"),
				.submenu = 0,
				.state = 0,
				.validStates = (const char*[]) {
					"1x",
					"2x",
					"3x",
					"4x",
					"5x",
					"6x",
				},
				.stateMappings = (const struct GUIVariant[]) {
					GUI_V_U(1),
					GUI_V_U(2),
					GUI_V_U(3),
					GUI_V_U(4),
					GUI_V_U(5),
					GUI_V_U(6),
				},
				.nStates = 6
			},
			{
				.title = "为<我们的太阳>使用内置亮度传感器",
				.data = GUI_V_S("useLightSensor"),
				.submenu = 0,
				.state = illuminanceAvailable,
				.validStates = (const char*[]) {
					"关闭",
					"打开",
				},
				.nStates = 2
			},
		},
		.nConfigExtra = 5,
		.setup = _setup,
		.teardown = NULL,
		.gameLoaded = _gameLoaded,
		.gameUnloaded = _gameUnloaded,
		.prepareForFrame = _prepareForFrame,
		.drawFrame = _drawFrame,
		.drawScreenshot = _drawScreenshot,
		.drawBKImage = _drawBKImage,
		.paused = _gameUnloaded,
		.unpaused = _gameLoaded,
		.incrementScreenMode = _incrementScreenMode,
		.setFrameLimiter = _setFrameLimiter,
		.pollGameInput = _pollGameInput,
		.running = _running
	};
	mGUIInit(&runner, "switch");

	// 映射GUI菜单按键
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_A, GUI_INPUT_SELECT);
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_B, GUI_INPUT_BACK);
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_X, GUI_INPUT_CANCEL);
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_Up, GUI_INPUT_UP);
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_Down, GUI_INPUT_DOWN);
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_Left, GUI_INPUT_LEFT);
	_mapKey(&runner.params.keyMap, AUTO_INPUT, HidNpadButton_Right, GUI_INPUT_RIGHT);

	// 启动音频输出
	audoutStartAudioOut();

	// 处理文件关联配置
	if (argc > 0) {
		struct VFile* vf = VFileOpen("romfs:/fileassoc.cfg.in", O_RDONLY);
		if (vf) {
			size_t size = vf->size(vf);
			const char* arg0 = strchr(argv[0], '/');
			char* buffer[2] = {
				calloc(size + 1, 1),
				malloc(size + strlen(arg0) + 1)
			};
			vf->read(vf, buffer[0], vf->size(vf));
			vf->close(vf);
			snprintf(buffer[1], size + strlen(arg0), buffer[0], arg0);
			mkdir("sdmc:/config/nx-hbmenu/fileassoc", 0755);
			vf = VFileOpen("sdmc:/config/nx-hbmenu/fileassoc/mgba.cfg", O_CREAT | O_TRUNC | O_WRONLY);
			if (vf) {
				vf->write(vf, buffer[1], strlen(buffer[1]));
				vf->close(vf);
			}
			free(buffer[0]);
			free(buffer[1]);
		}
	}

	// ===================beiklive
	mkdir(BK_CONFIG_BASE_PATH, 0755);
	mkdir(BK_LOGO_BASE_PATH, 0755);
	if (!bk_config_init()) {
        printf("配置管理器初始化失败\n");
        return 1;
    }
    // 获取全局运行器指针
	bk_global_runner = &runner;

	BK_LOG_INIT(BK_LOG_LEVEL_DEBUG, 1, 1);


	// ===================beiklive








	// 如果提供了游戏文件，直接运行游戏；否则显示菜单
	if (argc > 1) {
		size_t i;
		// 加载按键映射
		for (i = 0; runner.keySources[i].id; ++i) {
			mInputMapLoad(&runner.params.keyMap, runner.keySources[i].id, mCoreConfigGetInput(&runner.config));
		}
		// 直接运行指定的游戏
		mGUIRun(&runner, argv[1]);
	} else {
		// 显示游戏菜单
		mGUIRunloop(&runner);
	}

	// 清理GUI运行器
	mGUIDeinit(&runner);

	// 清理所有系统资源
	audoutStopAudioOut();
	GUIFontDestroy(font);

	glDeinit();
	bk_opengl_deinit();

	hidTeardown();

	psmExit();
	audoutExit();
	romfsExit();
	eglDeinit();
	socketExit();
	return 0;
}
