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

GLuint bkfbo; 
GLuint bkfboVao; 
GLuint bkfboVbo; 
GLuint bkfboTex;
GLuint bkShaderProgram;
bool useFBO = true;

static const GLfloat bkQuadVerts[] = {
    // x, y,      u, v
    -1.f, -1.f,  0.f, 0.f,
     1.f, -1.f,  1.f, 0.f,
     1.f,  1.f,  1.f, 1.f,
    -1.f,  1.f,  0.f, 1.f,
};


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
    glDeleteTextures(1, &bkMaskTexGBA);
    glDeleteTextures(1, &bkMaskTexGBC);
    glDeleteProgram(bkProgram);


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

void bk_init_fbo(int width, int height)
{
static const GLchar* const _gles2Header =
	"#version 100\n"
	"precision mediump float;\n";


// 顶点着色器：传递纹理坐标
static const char* const _vertexShader =
    "attribute vec4 position;\n"
    "attribute vec2 texcoord;\n"
    "varying vec2 texCoord;\n"
    
    "void main() {\n"
    "   gl_Position = position;\n"
    "   texCoord = texcoord;\n"
    "}";

static const char* const _fragmentShaderCRT =
    "varying vec2 texCoord;\n"
    "uniform sampler2D tex;\n"
    "uniform vec2 texSize;\n"
    "vec4 scale2x(vec4 pixels[5], vec2 p) {\n"
    "    p = fract(p);\n"
    "	if (p.x > .5) {\n"
    "		if (p.y > .5) {\n"
    "			return pixels[0] == pixels[3] && pixels[0] != pixels[1] && pixels[3] != pixels[4] ? pixels[3] : pixels[2];\n"
    "		} else {\n"
    "			return pixels[4] == pixels[3] && pixels[1] != pixels[4] && pixels[0] != pixels[3] ? pixels[3] : pixels[2];\n"
    "		}\n"
    "	} else {\n"
    "		if (p.y > .5) {\n"
    "			return pixels[1] == pixels[0] && pixels[0] != pixels[3] && pixels[1] != pixels[4] ? pixels[1] : pixels[2];\n"
    "		} else {\n"
    "			return pixels[1] == pixels[4] && pixels[1] != pixels[0] && pixels[4] != pixels[3] ? pixels[1] : pixels[2];\n"
    "		}\n"
    "	}\n"
    "}\n"
    "vec4 scaleNeighborhood(vec2 p, vec2 x, vec2 o) {\n"
    "	vec4 neighborhood[5];\n"
    "    neighborhood[0] = texture2D(tex, texCoord + x + vec2( 0.0,  o.y));\n"
    "    neighborhood[1] = texture2D(tex, texCoord + x + vec2(-o.x,  0.0));\n"
    "    neighborhood[2] = texture2D(tex, texCoord + x + vec2( 0.0,  0.0));\n"
    "    neighborhood[3] = texture2D(tex, texCoord + x + vec2( o.x,  0.0));\n"
    "    neighborhood[4] = texture2D(tex, texCoord + x + vec2( 0.0, -o.y));\n"
    "	return scale2x(neighborhood, p + x * texSize);\n"
    "}\n"
    "void main() {\n"
    "    vec2 o = 1.0 / texSize;\n"
    "    vec2 p = texCoord * texSize;\n"
    "	vec4 pixels[5];\n"
    "	pixels[0] = scaleNeighborhood(p, vec2(       0.0,  o.y / 2.0), o);\n"
    "	pixels[1] = scaleNeighborhood(p, vec2(-o.x / 2.0,        0.0), o);\n"
    "	pixels[2] = scaleNeighborhood(p, vec2(       0.0,        0.0), o);\n"
    "	pixels[3] = scaleNeighborhood(p, vec2( o.x / 2.0,        0.0), o);\n"
    "	pixels[4] = scaleNeighborhood(p, vec2(       0.0, -o.y / 2.0), o);\n"
    "	gl_FragColor = scale2x(pixels, p * 2.0);\n"
    "}\n";



    bkShaderProgram = glCreateProgram();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* shaderBuffer[2];
    shaderBuffer[0] = _gles2Header;
    shaderBuffer[1] = _vertexShader;

    glShaderSource(vertexShader, 2, shaderBuffer, NULL);
    glCompileShader(vertexShader);

    shaderBuffer[1] = _fragmentShaderCRT;  // 改为CRT着色器
    glShaderSource(fragmentShader, 2, shaderBuffer, NULL);
    glCompileShader(fragmentShader);

    glAttachShader(bkShaderProgram, vertexShader);
    glAttachShader(bkShaderProgram, fragmentShader);
    glLinkProgram(bkShaderProgram);


    glGenVertexArrays(1, &bkfboVao);
    glGenBuffers(1, &bkfboVbo);

    glBindVertexArray(bkfboVao);
    glBindBuffer(GL_ARRAY_BUFFER, bkfboVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bkQuadVerts), bkQuadVerts, GL_STATIC_DRAW);
    GLint posLoc = glGetAttribLocation(bkShaderProgram, "position");
    GLint uvLoc  = glGetAttribLocation(bkShaderProgram, "texcoord");
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);

    glEnableVertexAttribArray(uvLoc);
    glVertexAttribPointer(uvLoc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));

    glBindVertexArray(0);



    glGenFramebuffers(1, &bkfbo);
    glBindFramebuffer(GL_FRAMEBUFFER, bkfbo);
    glGenTextures(1, &bkfboTex);
    glBindTexture(GL_TEXTURE_2D, bkfboTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_COLOR_ATTACHMENT0,
        GL_TEXTURE_2D,
        bkfboTex,
        0
    );
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        printf("FBO incomplete: 0x%x\n", status);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);


}
void bk_switch_to_fbo(bool enable)
{
    if(enable)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, bkfbo);
        glClearColor(0,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}

void bk_render_fbo(GLuint *texture, int width, int height)
{
    glUseProgram(bkShaderProgram);
    glBindVertexArray(bkfboVao);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_NEAREST
	);

    glUniform1i(glGetUniformLocation(bkShaderProgram, "tex"), 0);

    
    glUniform2f(glGetUniformLocation(bkShaderProgram, "texSize"), (float)width, (float)height);

    // 使用三角扇绘制一个矩形（四个顶点）
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    
    // 解绑顶点数组
    glBindVertexArray(0);
    glUseProgram(0);
}

void bk_deinit_fbo(void){
    glDeleteProgram(bkShaderProgram);
    glDeleteFramebuffers(1, &bkfbo);
    glDeleteTextures(1, &bkfboTex);
    glDeleteVertexArrays(1, &bkfboVao);
    glDeleteBuffers(1, &bkfboVbo);
}