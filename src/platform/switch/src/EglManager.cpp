#include "EglManager.h"


bool EglManager::init()
{
	// 获取默认EGL显示器
	s_display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (!s_display) {
		return false;
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
		eglTerminate(s_display);
		s_display = NULL;
		return false;
	}

	// 创建EGL渲染表面
	s_surface = eglCreateWindowSurface(s_display, config, nwindowGetDefault(), NULL);
	if (!s_surface) {
		eglTerminate(s_display);
		s_display = NULL;
		return false;
	}

	// 创建OpenGL ES 3.1上下文
	EGLint contextAttributeList[] = {
		EGL_CONTEXT_MAJOR_VERSION, 3,  // 主版本号
		EGL_CONTEXT_MINOR_VERSION, 1,  // 次版本号
		EGL_NONE
	};
	s_context = eglCreateContext(s_display, config, EGL_NO_CONTEXT, contextAttributeList);
	if (!s_context) {
		eglDestroySurface(s_display, s_surface);
		s_surface = NULL;
		eglTerminate(s_display);
		s_display = NULL;
		return false;
	}

	// 激活上下文
	eglMakeCurrent(s_display, s_surface, s_surface, s_context);
	return true;

	
}

void EglManager::deinit()
{
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

void EglManager::swapBuffers() {
	eglSwapBuffers(s_display, s_surface);
}
