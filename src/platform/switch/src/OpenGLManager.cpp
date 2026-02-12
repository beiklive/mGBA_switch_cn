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

const char* const _bgfragmentShader = 
	"varying vec2 texCoord;\n"
	"void main() {\n"
	"	vec4 color = texture2D(0, texCoord);\n"
	"	gl_FragColor = color;\n"
	"}";

OpenGLManager::OpenGLManager()
    : background_tex(0)
    , menu_tex(0)
    , font_tex(0) { }
OpenGLManager::~OpenGLManager() {
	if (background_tex)
		glDeleteTextures(1, &background_tex);
	if (menu_tex)
		glDeleteTextures(1, &menu_tex);
	if (font_tex)
		glDeleteTextures(1, &font_tex);
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

void OpenGLManager::initBackgroundTexture(Vector2f ScreenHint) {
	if (background_tex)
		glDeleteTextures(1, &background_tex);
	background_tex = createEmptyTexture(ScreenHint);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    background_program = glCreateProgram();
    const GLchar* shaderBuffer[2];
    shaderBuffer[0] = _gles2Header;
    shaderBuffer[1] = _bgvertexShader;
    glShaderSource(vertexShader, 2, shaderBuffer, 0);
    shaderBuffer[1] = _bgfragmentShader;
    glShaderSource(fragmentShader, 2, shaderBuffer, 0);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);
	glAttachShader(background_program, fragmentShader);
	glAttachShader(background_program, vertexShader);
	glLinkProgram(background_program);



	int width, height, nrChannels;
	GLenum format = GL_RGB;
	unsigned char* data = utils::loadImage("romfs:/switchbg.png", &width, &height, &nrChannels, &format);
	if (data) {
		glBindTexture(GL_TEXTURE_2D, background_tex);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		free(data);
	}
}

void OpenGLManager::initMenuTexture(Vector2f ScreenHint) {
	if (menu_tex)
		glDeleteTextures(1, &menu_tex);
	menu_tex = createEmptyTexture(ScreenHint);
}

void OpenGLManager::initFontTexture(Vector2f ScreenHint) {
	if (font_tex)
		glDeleteTextures(1, &font_tex);
	font_tex = createEmptyTexture(ScreenHint);
}

}
