/* Copyright (c) 2013-2018 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
// 包含GUI字体、字体指标、PNG I/O和虚拟文件系统的头文件
#include <mgba-util/gui/font.h>
#include <mgba-util/gui/font-metrics.h>
#include <mgba-util/png-io.h>
#include <mgba-util/string.h>
#include <mgba-util/vfs.h>

// 包含OpenGL ES 3.0头文件，用于GPU渲染
#include <GLES3/gl3.h>
#include "font-cn.h"


// 定义字形高度为24像素
#define GLYPH_HEIGHT 24
// 定义单元格高度为32像素（用于纹理采样）
#define CELL_HEIGHT 32
// 定义单元格宽度为32像素
#define CELL_WIDTH 32
// 定义最大字形数量为1024个
#define MAX_GLYPHS 1024


/* 添加中文相关定义 */
#define CN_GLYPHS_START 0x4E00      // 常用汉字起始编码
#define CN_GLYPHS_COUNT 6763        // GB2312常用汉字数量
#define CN_CELLS_PER_ROW 128        // 中文字体纹理每行单元格数
#define CN_CELL_SIZE 32             // 中文字符单元格大小（像素）



// 定义四边形顶点的偏移坐标（用于GPU渲染，范围0-1）
static const GLfloat _offsets[] = {
	0.f, 0.f,  // 左下角
	1.f, 0.f,  // 右下角
	1.f, 1.f,  // 右上角
	0.f, 1.f,  // 左上角
};

// OpenGL ES 3.0着色器的通用头部（版本声明和精度设置）
static const GLchar* const _gles3Header =
	"#version 300 es\n"
	"precision mediump float;\n";

// 顶点着色器：计算顶点位置和纹理坐标
static const char* const _vertexShader =
	"in vec2 offset;\n"
	"in vec3 origin;\n"
	"in vec2 glyph;\n"
	"in vec2 dims;\n"
	"in mat2 transform;\n"
	"in vec4 color;\n"
	"out vec4 fragColor;\n"
	"out vec2 texCoord;\n"

	"void main() {\n"
	// 计算纹理坐标：(字形位置 + 偏移 * 尺寸) / 512（纹理大小）
	"	texCoord = (glyph + offset * dims) / vec2(4096.0, 2208.0);\n"
	// 应用变换矩阵并缩放偏移
	"	vec2 scaledOffset = (transform * (offset * 2.0 - vec2(1.0)) + vec2(1.0)) / 2.0 * dims;\n"
	"	fragColor = color;\n"
	// 计算最终的屏幕坐标（归一化设备坐标：-1到1）
	"	gl_Position = vec4((origin.x + scaledOffset.x) / 640.0 - 1.0, -(origin.y + scaledOffset.y) / 360.0 + 1.0, origin.z, 1.0);\n"
	"}";

// 片段着色器：计算最终像素颜色（带alpha混合和颜色调制）
static const char* const _fragmentShader =
	"in vec2 texCoord;\n"
	"in vec4 fragColor;\n"
	"out vec4 outColor;\n"
	"uniform sampler2D tex;\n"
	"uniform float cutoff;\n"
	"uniform vec3 colorModulus;\n"

	"void main() {\n"
	// 从纹理中采样颜色
	"	vec4 texColor = texture2D(tex, texCoord);\n"

	// 应用颜色调制（RGB分量乘以调制值）
	"	texColor.rgb = fragColor.rgb * colorModulus;\n"
	// 应用片段颜色的alpha值
	"	texColor.a *= fragColor.a;\n"
	"	outColor = texColor;\n"
	"}";

// GUI字体结构体：包含所有渲染所需的GPU资源和数据
struct GUIFont {
	GLuint font;                       // 字体纹理ID
	int currentGlyph;                  // 当前批处理中的字形数量
	GLuint program;                    // GPU着色器程序
	GLuint vbo;                        // 顶点缓冲对象（偏移）
	GLuint vao;                        // 顶点数组对象
	GLuint texLocation;                // 纹理采样器uniform位置
	GLuint cutoffLocation;             // cutoff uniform位置
	GLuint colorModulusLocation;       // colorModulus uniform位置

	// 属性位置
	GLuint originLocation;             // 原点属性位置
	GLuint glyphLocation;              // 字形位置属性位置
	GLuint dimsLocation;               // 尺寸属性位置
	GLuint transformLocation[2];       // 变换矩阵属性位置（2行）
	GLuint colorLocation;              // 颜色属性位置

	// 顶点缓冲对象ID
	GLuint originVbo;                  // 原点数据VBO
	GLuint glyphVbo;                   // 字形位置数据VBO
	GLuint dimsVbo;                    // 尺寸数据VBO
	GLuint transformVbo[2];            // 变换矩阵数据VBO（2个）
	GLuint colorVbo;                   // 颜色数据VBO

	// CPU端数据缓冲（稍后上传到GPU）
	GLfloat originData[MAX_GLYPHS][3];    // 每个字形的x,y,z原点
	GLfloat glyphData[MAX_GLYPHS][2];     // 每个字形在纹理中的位置
	GLfloat dimsData[MAX_GLYPHS][2];      // 每个字形的宽度和高度
	GLfloat transformData[2][MAX_GLYPHS][2]; // 每个字形的变换矩阵（2x2）
	GLfloat colorData[MAX_GLYPHS][4];     // 每个字形的RGBA颜色
};

// 从PNG文件加载字体纹理
static bool _loadTexture(const char* path) {
	// 以只读模式打开文件
	struct VFile* vf = VFileOpen(path, O_RDONLY);
	if (!vf) {
		return false;
	}
	// 打开PNG读取器
	png_structp png = PNGReadOpen(vf, 0);
	// 创建PNG信息结构体
	png_infop info = png_create_info_struct(png);
	png_infop end = png_create_info_struct(png);
	bool success = false;
	// 读取PNG头部信息
	if (png && info && end) {
		success = PNGReadHeader(png, info);
	}
	void* pixels = NULL;
	if (success) {
		// 获取图像宽度和高度
		unsigned height = png_get_image_height(png, info);
		unsigned width = png_get_image_width(png, info);
		// 分配像素数据缓冲
		pixels = malloc(width * height);
		if (pixels) {
			// 读取PNG像素数据（8位灰度值，用于alpha通道）
			success = PNGReadPixels8(png, info, pixels, width, height, width);
			// 读取PNG尾部
			success = success && PNGReadFooter(png, end);
		} else {
			success = false;
		}
		// 将像素数据上传到GPU纹理
		if (success) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, width, height, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
		}
	}
	// 关闭PNG读取器和文件
	PNGReadClose(png, info, end);
	if (pixels) {
		free(pixels);
	}
	vf->close(vf);
	return success;
}

// 创建GUI字体对象
struct GUIFont* GUIFontCreate(void) {
	// 分配内存
	struct GUIFont* font = malloc(sizeof(struct GUIFont));
	if (!font) {
		return NULL;
	}
	
	// 创建并配置字体纹理
	glGenTextures(1, &font->font);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->font);
	// 设置纹理换行模式为边界夹紧（避免纹理边界伪影）
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// 设置纹理过滤方式为线性过滤（更平滑）
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// 从资源文件加载字体纹理
	if (!_loadTexture("romfs:/font-cn.png")) {
        if (!_loadTexture("romfs:/font-new.png")) {
            GUIFontDestroy(font);
            return NULL;
        }
    }


	font->currentGlyph = 0;
	// 创建着色器程序
	font->program = glCreateProgram();
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const GLchar* shaderBuffer[2];

	// 编译顶点着色器
	shaderBuffer[0] = _gles3Header;
	shaderBuffer[1] = _vertexShader;
	glShaderSource(vertexShader, 2, shaderBuffer, NULL);

	// 编译片段着色器
	shaderBuffer[1] = _fragmentShader;
	glShaderSource(fragmentShader, 2, shaderBuffer, NULL);

	// 将着色器附加到程序
	glAttachShader(font->program, vertexShader);
	glAttachShader(font->program, fragmentShader);

	// 编译并检查片段着色器
	glCompileShader(fragmentShader);
	GLint success;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar msg[512];
		glGetShaderInfoLog(fragmentShader, sizeof(msg), NULL, msg);
		puts(msg);
	}

	// 编译并检查顶点着色器
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar msg[512];
		glGetShaderInfoLog(vertexShader, sizeof(msg), NULL, msg);
		puts(msg);
	}

	// 链接程序并检查结果
	glLinkProgram(font->program);
	glGetProgramiv(font->program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar msg[512];
		glGetProgramInfoLog(font->program, sizeof(msg), NULL, msg);
		puts(msg);
	}

	// 删除着色器对象（已链接到程序）
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// 获取uniform变量位置
	font->texLocation = glGetUniformLocation(font->program, "tex");
	font->cutoffLocation = glGetUniformLocation(font->program, "cutoff");
	font->colorModulusLocation = glGetUniformLocation(font->program, "colorModulus");

	// 获取属性变量位置
	font->originLocation = glGetAttribLocation(font->program, "origin");
	font->glyphLocation = glGetAttribLocation(font->program, "glyph");
	font->dimsLocation = glGetAttribLocation(font->program, "dims");
	font->transformLocation[0] = glGetAttribLocation(font->program, "transform");
	font->transformLocation[1] = font->transformLocation[0] + 1; // mat2占两个属性
	font->colorLocation = glGetAttribLocation(font->program, "color");

	GLuint offsetLocation = glGetAttribLocation(font->program, "offset");

	// 创建并配置顶点数组对象
	glGenVertexArrays(1, &font->vao);
	glBindVertexArray(font->vao);

	// 设置偏移属性（每个顶点一份，不使用实例化）
	glGenBuffers(1, &font->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, font->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_offsets), _offsets, GL_STATIC_DRAW);
	glVertexAttribPointer(offsetLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(offsetLocation, 0);
	glEnableVertexAttribArray(offsetLocation);

	// 设置原点属性（每个实例一份）
	glGenBuffers(1, &font->originVbo);
	glBindBuffer(GL_ARRAY_BUFFER, font->originVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(font->originLocation, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(font->originLocation, 1); // 每个实例改变一次
	glEnableVertexAttribArray(font->originLocation);

	// 设置字形位置属性
	glGenBuffers(1, &font->glyphVbo);
	glBindBuffer(GL_ARRAY_BUFFER, font->glyphVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(font->glyphLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(font->glyphLocation, 1);
	glEnableVertexAttribArray(font->glyphLocation);

	// 设置尺寸属性
	glGenBuffers(1, &font->dimsVbo);
	glBindBuffer(GL_ARRAY_BUFFER, font->dimsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(font->dimsLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(font->dimsLocation, 1);
	glEnableVertexAttribArray(font->dimsLocation);

	// 设置变换矩阵属性（2x2矩阵需要2个属性）
	glGenBuffers(2, font->transformVbo);
	glBindBuffer(GL_ARRAY_BUFFER, font->transformVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(font->transformLocation[0], 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(font->transformLocation[0], 1);
	glEnableVertexAttribArray(font->transformLocation[0]);
	glBindBuffer(GL_ARRAY_BUFFER, font->transformVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(font->transformLocation[1], 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(font->transformLocation[1], 1);
	glEnableVertexAttribArray(font->transformLocation[1]);

	// 设置颜色属性
	glGenBuffers(1, &font->colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, font->colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glVertexAttribPointer(font->colorLocation, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribDivisor(font->colorLocation, 1);
	glEnableVertexAttribArray(font->colorLocation);

	glBindVertexArray(0);

	return font;
}

// 销毁GUI字体对象并释放GPU资源
void GUIFontDestroy(struct GUIFont* font) {
	// 删除所有顶点缓冲对象
	glDeleteBuffers(1, &font->vbo);
	glDeleteBuffers(1, &font->originVbo);
	glDeleteBuffers(1, &font->glyphVbo);
	glDeleteBuffers(1, &font->dimsVbo);
	glDeleteBuffers(2, font->transformVbo);
	glDeleteBuffers(1, &font->colorVbo);
	// 删除着色器程序
	glDeleteProgram(font->program);
	// 删除纹理
	glDeleteTextures(1, &font->font);
	// 删除顶点数组对象
	glDeleteVertexArrays(1, &font->vao);
	// 释放内存
	free(font);
}

// 获取字体的高度（单位：像素）
unsigned GUIFontHeight(const struct GUIFont* font) {
	UNUSED(font);
	return CELL_WIDTH;
}

// 获取单个字形的宽度
unsigned GUIFontGlyphWidth(const struct GUIFont* font, uint32_t glyph) {
	UNUSED(font);
	/* 中文字符固定宽度 */
    if (glyph >= CN_GLYPHS_START && glyph < CHINESE_GLYPHS_FINISH) {
        return 28;
    }
    

	// 如果字符代码超过ASCII范围，用'?'替代
	if (glyph > 0x7F) {
		glyph = '?';
	}
	// 从预定义的字体指标获取宽度，乘以2用于缩放
	return defaultFontMetrics[glyph].width * 2;
}

// 获取图标的尺寸
void GUIFontIconMetrics(const struct GUIFont* font, enum GUIIcon icon, unsigned* w, unsigned* h) {
	UNUSED(font);
	// 检查图标ID是否有效
	if (icon >= GUI_ICON_MAX) {
		// 无效图标，返回0尺寸
		if (w) {
			*w = 0;
		}
		if (h) {
			*h = 0;
		}
	} else {
		// 从预定义的图标指标获取尺寸，乘以2用于缩放
		if (w) {
			*w = defaultIconMetrics[icon].width * 2;
		}
		if (h) {
			*h = defaultIconMetrics[icon].height * 2;
		}
	}
}
// 二分查找实现（假设映射表已按unicode升序排序）
static const ChineseGlyphInfo* binary_search_chinese_glyph(uint32_t unicode) {
    int left = 0;
    int right = CHINESE_GLYPH_COUNT - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        uint32_t mid_unicode = chinese_glyphs[mid].unicode;
        
        if (mid_unicode == unicode) {
            return &chinese_glyphs[mid];
        } else if (mid_unicode < unicode) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return NULL;
}

void GUIFontDrawGlyph(struct GUIFont* font, int x, int y, uint32_t color, uint32_t unicode) {
    struct GUIFontGlyphMetric metric;
    
	unicode = normalize_cn_symbol(unicode);
	// printf("(U+%04X) (x: %d, y: %d)\n", unicode, x, y);
	if (unicode >= CN_GLYPHS_START && unicode < CHINESE_GLYPHS_FINISH) 
	{
		const ChineseGlyphInfo* cn_info = binary_search_chinese_glyph(unicode);
		if (cn_info != NULL) {
			// printf("find cn_info: U+%04X (%u) (x:%d, y:%d)\n", cn_info->unicode, cn_info->unicode, cn_info->tex_x, cn_info->tex_y);
			/* 简单的中文字符度量 - 固定宽度 */
			metric.width = 14;
			metric.height = 12;
			metric.padding.left = 2;
			metric.padding.right = 2;
			metric.padding.top = 4;
			metric.padding.bottom = 4;
			
			if (font->currentGlyph >= MAX_GLYPHS) {
				GUIFontDrawSubmit(font);
			}
			
			int offset = font->currentGlyph;
			int tex_row = cn_info->tex_y;
			int tex_col = cn_info->tex_x;
			
			
			// printf("[DEBUG] Unicode: U+%04X (%u) (x:%d, y:%d)\n", unicode, unicode, tex_col, tex_row);
			
			/* 使用中文字符纹理坐标 */
			font->originData[offset][0] = x;
			font->originData[offset][1] = y - CELL_WIDTH + 9;
			font->originData[offset][2] = 0;
			font->glyphData[offset][0] = tex_col + metric.padding.left;
			font->glyphData[offset][1] = tex_row + metric.padding.top; /* 中文字符在纹理下半部分 */
			font->dimsData[offset][0] = CELL_WIDTH - (metric.padding.left + metric.padding.right);
			font->dimsData[offset][1] = CELL_HEIGHT - (metric.padding.top + metric.padding.bottom);
			font->transformData[0][offset][0] = 1.0f;
			font->transformData[0][offset][1] = 0.0f;
			font->transformData[1][offset][0] = 0.0f;
			font->transformData[1][offset][1] = 1.0f;
			font->colorData[offset][0] = (color & 0xFF) / 255.0f;
			font->colorData[offset][1] = ((color >> 8) & 0xFF) / 255.0f;
			font->colorData[offset][2] = ((color >> 16) & 0xFF) / 255.0f;
			font->colorData[offset][3] = ((color >> 24) & 0xFF) / 255.0f;
			
			++font->currentGlyph;
			return;
		}
		else{
			/* 其他非ASCII字符显示为问号 */
			unicode = '?';
		}
	}
	else if (unicode > 0x7F) {
		/* 其他非ASCII字符显示为问号 */
		unicode = '?';
	}
    
    /* 原有的英文字符处理逻辑 */
    metric = defaultFontMetrics[unicode];

	// 如果批处理已满，提交当前批处理
	if (font->currentGlyph >= MAX_GLYPHS) {
		GUIFontDrawSubmit(font);
	}

	int offset = font->currentGlyph;

	// 设置字形的屏幕位置（原点）
	font->originData[offset][0] = x;
	font->originData[offset][1] = y - CELL_WIDTH + 5 * 2;
	font->originData[offset][2] = 0;
	
	// 计算字形在纹理中的位置（16x16网格布局）
	font->glyphData[offset][0] = (unicode & 15) * CELL_WIDTH + metric.padding.left;
	font->glyphData[offset][1] = (unicode >> 4) * CELL_HEIGHT + metric.padding.top;
	
	// 设置字形的尺寸（考虑padding）
	font->dimsData[offset][0] = CELL_WIDTH - (metric.padding.left + metric.padding.right);
	font->dimsData[offset][1] = CELL_HEIGHT - (metric.padding.top + metric.padding.bottom);
	
	// 设置变换矩阵为单位矩阵（无变换）
	font->transformData[0][offset][0] = 1.0f;
	font->transformData[0][offset][1] = 0.0f;
	font->transformData[1][offset][0] = 0.0f;
	font->transformData[1][offset][1] = 1.0f;
	
	// 将32位RGBA颜色转换为0-1范围的浮点值
	font->colorData[offset][0] = (color & 0xFF) / 255.0f;
	font->colorData[offset][1] = ((color >> 8) & 0xFF) / 255.0f;
	font->colorData[offset][2] = ((color >> 16) & 0xFF) / 255.0f;
	font->colorData[offset][3] = ((color >> 24) & 0xFF) / 255.0f;

	++font->currentGlyph;
}

// 添加一个图标到当前批处理（支持对齐和方向）
void GUIFontDrawIcon(struct GUIFont* font, int x, int y, enum GUIAlignment align, enum GUIOrientation orient, uint32_t color, enum GUIIcon icon) {
	// 检查图标ID是否有效
	if (icon >= GUI_ICON_MAX) {
		return;
	}
	// 获取图标的指标信息
	struct GUIIconMetric metric = defaultIconMetrics[icon];

	// 初始化翻转标志（用于水平/垂直翻转）
	float hFlip = 1.0f;
	float vFlip = 1.0f;
	
	// 根据对齐方式调整x坐标
	switch (align & GUI_ALIGN_HCENTER) {
	case GUI_ALIGN_HCENTER:
		x -= metric.width;
		break;
	case GUI_ALIGN_RIGHT:
		x -= metric.width * 2;
		break;
	}
	
	// 根据对齐方式调整y坐标
	switch (align & GUI_ALIGN_VCENTER) {
	case GUI_ALIGN_VCENTER:
		y -= metric.height;
		break;
	case GUI_ALIGN_BOTTOM:
		y -= metric.height * 2;
		break;
	}

	// 根据方向应用变换
	switch (orient) {
	case GUI_ORIENT_HMIRROR:
		// 水平翻转
		hFlip = -1.0;
		break;
	case GUI_ORIENT_VMIRROR:
		// 垂直翻转
		vFlip = -1.0;
		break;
	case GUI_ORIENT_0:
	default:
		// TODO: 实现旋转功能
		break;
	}
	
	// 如果批处理已满，提交当前批处理
	if (font->currentGlyph >= MAX_GLYPHS) {
		GUIFontDrawSubmit(font);
	}

	int offset = font->currentGlyph;

	font->originData[offset][0] = x;
	font->originData[offset][1] = y;
	font->originData[offset][2] = 0;
	// 图标位置在纹理的下半部分（y偏移256）
	font->glyphData[offset][0] = metric.x * 2;
	font->glyphData[offset][1] = metric.y * 2 + 256;
	font->dimsData[offset][0] = metric.width * 2;
	font->dimsData[offset][1] = metric.height * 2;
	// 应用翻转变换
	font->transformData[0][offset][0] = hFlip;
	font->transformData[0][offset][1] = 0.0f;
	font->transformData[1][offset][0] = 0.0f;
	font->transformData[1][offset][1] = vFlip;
	font->colorData[offset][0] = (color & 0xFF) / 255.0f;
	font->colorData[offset][1] = ((color >> 8) & 0xFF) / 255.0f;
	font->colorData[offset][2] = ((color >> 16) & 0xFF) / 255.0f;
	font->colorData[offset][3] = ((color >> 24) & 0xFF) / 255.0f;

	++font->currentGlyph;
}

// 添加一个指定尺寸的图标到当前批处理
void GUIFontDrawIconSize(struct GUIFont* font, int x, int y, int w, int h, uint32_t color, enum GUIIcon icon) {
	// 检查图标ID是否有效
	if (icon >= GUI_ICON_MAX) {
		return;
	}
	// 获取图标的指标信息
	struct GUIIconMetric metric = defaultIconMetrics[icon];

	// 使用默认尺寸（如果指定的尺寸为0）
	if (!w) {
		w = metric.width * 2;
	}
	if (!h) {
		h = metric.height * 2;
	}

	// 如果批处理已满，提交当前批处理
	if (font->currentGlyph >= MAX_GLYPHS) {
		GUIFontDrawSubmit(font);
	}

	int offset = font->currentGlyph;

	// 计算中心对齐的位置
	font->originData[offset][0] = x + w / 2 - metric.width;
	font->originData[offset][1] = y + h / 2 - metric.height;
	font->originData[offset][2] = 0;
	// ...existing code...
	font->glyphData[offset][0] = metric.x * 2;
	font->glyphData[offset][1] = metric.y * 2 + 256;
	font->dimsData[offset][0] = metric.width * 2;
	font->dimsData[offset][1] = metric.height * 2;
	// 根据指定尺寸计算缩放变换
	font->transformData[0][offset][0] = w * 0.5f / metric.width;
	font->transformData[0][offset][1] = 0.0f;
	font->transformData[1][offset][0] = 0.0f;
	font->transformData[1][offset][1] = h * 0.5f / metric.height;
	font->colorData[offset][0] = (color & 0xFF) / 255.0f;
	font->colorData[offset][1] = ((color >> 8) & 0xFF) / 255.0f;
	font->colorData[offset][2] = ((color >> 16) & 0xFF) / 255.0f;
	font->colorData[offset][3] = ((color >> 24) & 0xFF) / 255.0f;

	++font->currentGlyph;
}

// 提交当前批处理的所有字形/图标到GPU并绘制
void GUIFontDrawSubmit(struct GUIFont* font) {
	// 启用着色器程序
	glUseProgram(font->program);
	// 绑定顶点数组对象
	glBindVertexArray(font->vao);
	// 绑定字体纹理
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, font->font);

	// 启用alpha混合（用于透明度）
	glEnable(GL_BLEND);
	// 设置混合模式：源alpha预乘，1减源alpha作为目标
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// 绑定纹理采样器
	glUniform1i(font->texLocation, 0);

	// 上传原点数据到GPU
	glBindBuffer(GL_ARRAY_BUFFER, font->originVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * font->currentGlyph, font->originData);

	// 上传字形位置数据到GPU
	glBindBuffer(GL_ARRAY_BUFFER, font->glyphVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * font->currentGlyph, font->glyphData);

	// 上传尺寸数据到GPU
	glBindBuffer(GL_ARRAY_BUFFER, font->dimsVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * font->currentGlyph, font->dimsData);

	// 上传变换矩阵的第一行到GPU
	glBindBuffer(GL_ARRAY_BUFFER, font->transformVbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * font->currentGlyph, font->transformData[0]);

	// 上传变换矩阵的第二行到GPU
	glBindBuffer(GL_ARRAY_BUFFER, font->transformVbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * font->currentGlyph, font->transformData[1]);

	// 上传颜色数据到GPU
	glBindBuffer(GL_ARRAY_BUFFER, font->colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * MAX_GLYPHS, NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * font->currentGlyph, font->colorData);

	// 第一次绘制：绘制黑色阴影（使用低cutoff值）
	glUniform1f(font->cutoffLocation, 0.1f);
	glUniform3f(font->colorModulusLocation, 0.f, 0.f, 0.f); // 黑色
	// 使用实例化绘制：每个实例一个四边形（4个顶点）
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, font->currentGlyph);

	// 第二次绘制：绘制彩色文本（使用高cutoff值）
	glUniform1f(font->cutoffLocation, 0.6f);
	glUniform3f(font->colorModulusLocation, 1.f, 1.f, 1.f); // 白色调制
	glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, font->currentGlyph);

	// 重置计数器，准备下一个批处理
	font->currentGlyph = 0;

	// 解绑顶点数组和程序
	glBindVertexArray(0);
	glUseProgram(0);
}
