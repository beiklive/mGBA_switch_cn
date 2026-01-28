#include <beiklive/beiklive.h>

GLuint bkTex;
GLuint bkMaskTexGBA;
GLuint bkMaskTexGBC;
GLuint bkProgram;
GLuint bktexLocation;         // 纹理uniform位置
GLuint bkdimsLocation;        // 尺寸uniform位置
GLuint bkinsizeLocation;      // 输入大小uniform位置
GLuint bkcolorLocation;       // 颜色uniform位置
GLuint bkvbo;                 // 顶点缓冲对象
GLuint bkvao;                 // 顶点数组对象

// 定义四边形顶点的偏移坐标（0-1范围）
static const GLfloat _offsets[] = {
	0.f, 0.f,  // 左下角
	1.f, 0.f,  // 右下角
	1.f, 1.f,  // 右上角
	0.f, 1.f,  // 左上角
};

color_t* pixels = NULL;

bool bk_opengl_init(void)
{
    const GLchar* const _gles2Header =
	"#version 100\n"
	"precision mediump float;\n";

const char* const _vertexShader =
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

const char* const _fragmentShader =
	"varying vec2 texCoord;\n"     // 纹理坐标
	"uniform sampler2D tex;\n"     // 游戏画面纹理
	"uniform vec4 color;\n"        // 颜色调制（只使用RGB）

	"void main() {\n"
	"	vec4 texColor = texture2D(tex, texCoord);\n"
	"	gl_FragColor = texColor;\n"
	"}";

// 编译和链接着色器...
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    const GLchar* shaderBuffer[2];
	shaderBuffer[0] = _gles2Header;
	shaderBuffer[1] = _vertexShader;

    glShaderSource(vertexShader, 2, shaderBuffer, NULL);
    glCompileShader(vertexShader);
    
    shaderBuffer[1] = _fragmentShader;
    glShaderSource(fragmentShader, 2, shaderBuffer, NULL);
    glCompileShader(fragmentShader);
    
    bkProgram = glCreateProgram();
    glAttachShader(bkProgram, vertexShader);
    glAttachShader(bkProgram, fragmentShader);
    glLinkProgram(bkProgram);

	// 删除着色器对象
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	bktexLocation = glGetUniformLocation(bkProgram, "tex");
	bkcolorLocation = glGetUniformLocation(bkProgram, "color");
	bkdimsLocation = glGetUniformLocation(bkProgram, "dims");
	bkinsizeLocation = glGetUniformLocation(bkProgram, "insize");

	GLuint offsetLocation = glGetAttribLocation(bkProgram, "offset");

	// 创建顶点缓冲和数组对象
	glGenBuffers(1, &bkvbo);
	glGenVertexArrays(1, &bkvao);
	glBindVertexArray(bkvao);
	glBindBuffer(GL_ARRAY_BUFFER, bkvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_offsets), _offsets, GL_STATIC_DRAW);
	glVertexAttribPointer(offsetLocation, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(offsetLocation);
	glBindVertexArray(0);



	// BKMARK 背景绘制纹理
	glGenTextures(1, &bkTex);
	glBindTexture(GL_TEXTURE_2D, bkTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);


	glGenTextures(1, &bkMaskTexGBA);
	glBindTexture(GL_TEXTURE_2D, bkMaskTexGBA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glGenTextures(1, &bkMaskTexGBC);
	glBindTexture(GL_TEXTURE_2D, bkMaskTexGBC);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void bk_opengl_deinit(void) { 
    glDeleteTextures(1, &bkTex);
}

void _bk_util_draw_menu_background(struct GUIBackground* background, void* title)
{
    UNUSED(title);
    struct mGUIBackground* gbaBackground = (struct mGUIBackground*) background;
    int themeType = BK_THEME_DEFAULT;
	BK_GLOBAL_INT_GET(BK_META_CONFIG_THEME, themeType);
    if(gbaBackground->p->drawBKImage && themeType == BK_THEME_SWITCH)
    {
        gbaBackground->p->drawBKImage(
            gbaBackground->p,
            gbaBackground->image
        );
    }

}


int bk_init_menu_background(const char* filepath)
{
    if(!filepath)
        return 0;
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(0);
    unsigned char* data = stbi_load(filepath, &width, &height, &nrChannels, 0);
    int success = false;  // 初始化成功标志
    if (data) {

        GLenum format = GL_RGB;
        if (nrChannels == 4) format = GL_RGBA;
        else if (nrChannels == 1) format = GL_RED;
        
        glBindTexture(GL_TEXTURE_2D, bkTex);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        stbi_image_free(data);
        success = true;
    }else{
        success = false;
    }
    return success;
}

void bk_init_mask_texture(const char* filepath, int maskType){
    char* maskpath = bk_util_str_concatenate("sdmc:", filepath);
    
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(0);
    unsigned char* data = stbi_load(maskpath, &width, &height, &nrChannels, 0);
    int success = false;  // 初始化成功标志
    if (data) {

        GLenum format = GL_RGB;
        if (nrChannels == 4) format = GL_RGBA;
        else if (nrChannels == 1) format = GL_RED;
        
        glBindTexture(GL_TEXTURE_2D, maskType == 0 ? bkMaskTexGBA : bkMaskTexGBC);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        
        stbi_image_free(data);
        success = true;
    }else{
        success = false;
    }
    free(maskpath);
    BK_GLOBAL_INT_SET(maskType == 0 ? BK_META_MASK_STATUS_GBA : BK_META_MASK_STATUS_GBC, success);
}