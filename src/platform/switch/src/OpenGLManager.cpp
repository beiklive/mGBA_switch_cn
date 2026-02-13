#include "OpenGLManager.h"

namespace beiklive {
const GLfloat bkQuadVerts[] = {
    // x, y,      u, v
    -1.f, -1.f,  0.f, 0.f,
     1.f, -1.f,  1.f, 0.f,
     1.f,  1.f,  1.f, 1.f,
    -1.f,  1.f,  0.f, 1.f,
};

const GLchar* const _gles2Header =
	"#version 100\n"
	"precision mediump float;\n";

const char* const _bgvertexShader =
    "attribute vec4 position;\n"
    "attribute vec2 texcoord;\n"
    "varying vec2 texCoord;\n"
    
    "void main() {\n"
    "   gl_Position = position;\n"
    "   texCoord = texcoord;\n"
    "}";

// 定义四边形顶点的偏移坐标（0-1范围）
static const GLfloat _offsets[] = {
	0.f, 0.f,  // 左下角
	1.f, 0.f,  // 右下角
	1.f, 1.f,  // 右上角
	0.f, 1.f,  // 左上角
};

const char* const _bgfragmentShader = 
	"varying vec2 texCoord;\n"
	"uniform sampler2D tex;\n"
	"void main() {\n"
	"	vec4 color = texture2D(tex, texCoord);\n"
	"	gl_FragColor = color;\n"
	"}";

// 预处理顶点着色器  转换为 switch 坐标
const char* const _prevertexShader =
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
const char* const _prefragmentShader =
	"varying vec2 texCoord;\n"     // 接收顶点纹理坐标
	"uniform sampler2D tex;\n"     // 游戏画面纹理
	"uniform vec4 color;\n"        // 颜色调制
	"uniform float Brightness;\n"

	"void main() {\n"
	"    vec4 adjustedColor = texture2D(tex, texCoord);\n"
	"    adjustedColor.rgb *= vec3(1.0, 1.0, 1.0) * Brightness;\n"
	"    vec4 texColor = vec4(adjustedColor.rgb, 1.0);\n"
	"    texColor *= color;\n"
	"    gl_FragColor = texColor;\n"
	"}";


OpenGLManager::OpenGLManager(){ }
OpenGLManager::~OpenGLManager() {
}

void OpenGLManager::deleteGL(GLES2Shader* gl) {
	if (gl) {
		if (gl->program)
			glDeleteProgram(gl->program);
		if (gl->fragmentShader)
			glDeleteShader(gl->fragmentShader);
		if (gl->vertexShader)
			glDeleteShader(gl->vertexShader);
		if (gl->vao)
			glDeleteVertexArrays(1, &gl->vao);
		if (gl->vbo)
			glDeleteBuffers(1, &gl->vbo);
		if (gl->fbo)
			glDeleteFramebuffers(1, &gl->fbo);
		if (gl->tex)
			glDeleteTextures(1, &gl->tex);
		delete gl;
	}
 }

GLuint OpenGLManager::createEmptyTexture(Vector2f size) {
	GLuint textureID = 0;
	glGenTextures(1, &textureID);

	if (textureID != 0) {
		glBindTexture(GL_TEXTURE_2D, textureID);

		// 设置纹理参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// 对于Nintendo Switch开发，确保宽度和高度是有效的
		if (size.x > 0 && size.y > 0) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, static_cast<GLsizei>(size.x), static_cast<GLsizei>(size.y), 0,
			             GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		}

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	return textureID;
}




void OpenGLManager::initPreprocessShader(Vector2f ScreenHint) { 
	preprocess_gl = new GLES2PreprocessShader();
	preprocess_gl->tex = createEmptyTexture(ScreenHint);
	initShader(preprocess_gl, ShaderType::Preprocess);


	int width, height, nrChannels;
	GLenum format = GL_RGB;
	unsigned char* data = utils::loadImage("romfs:/switchbg.png", &width, &height, &nrChannels, &format);
	if (data) {
		glBindTexture(GL_TEXTURE_2D, preprocess_gl->tex);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		free(data);
	}

}

void OpenGLManager::initShader(GLES2PreprocessShader * gl, ShaderType type) {
    // 编译着色器程序
	gl->program = GetProgram(type);
	
	// fbo
	glGenFramebuffers(1, &gl->fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, gl->fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gl->tex, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//vao vbo
	glGenVertexArrays(1, &gl->vao);
	glBindVertexArray(gl->vao);
	glGenBuffers(1, &gl->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
	if (type == ShaderType::Preprocess)
	{
		gl->texLocation = glGetUniformLocation(gl->program, "tex");
		gl->dimsLocation = glGetUniformLocation(gl->program, "dims");
		gl->colorLocation = glGetUniformLocation(gl->program, "color");
		gl->insizeLocation = glGetUniformLocation(gl->program, "insize");
		gl->brightnessLocation = glGetUniformLocation(gl->program, "Brightness");
		gl->offsetLocation = glGetAttribLocation(gl->program, "offset");

		glBindBuffer(GL_ARRAY_BUFFER, gl->vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(_offsets), _offsets, GL_STATIC_DRAW);
		glVertexAttribPointer(gl->offsetLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(gl->offsetLocation);
	}
	else{
		glBufferData(GL_ARRAY_BUFFER, sizeof(bkQuadVerts), bkQuadVerts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	


}
GLuint OpenGLManager::GetProgram(ShaderType type) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint program = glCreateProgram();
	const GLchar* shaderBuffer[2];
    shaderBuffer[0] = _gles2Header;
	switch(type){
		case ShaderType::None:
			return GLuint();
		case ShaderType::Preprocess:
			shaderBuffer[1] = _prevertexShader;
			glShaderSource(vertexShader, 2, shaderBuffer, 0);
			shaderBuffer[1] = _prefragmentShader;
			glShaderSource(fragmentShader, 2, shaderBuffer, 0);
			break;
	}

	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	glAttachShader(program, fragmentShader);
	glAttachShader(program, vertexShader);
	glLinkProgram(program);

	return program;
}
}
