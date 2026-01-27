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
    struct mGUIBackground* gbaBackground = (struct mGUIBackground*) background;
    bool success;
    unsigned width, height;
    bool isSame = false;
    if(gbaBackground->p->drawBKImage)
    {
		struct VFile* vf = bk_util_open_png(BK_DEFAULT_LOGO_FILE, O_RDONLY);
		if (vf) {
			png_structp png = PNGReadOpen(vf, PNG_HEADER_BYTES);
			png_infop info = png_create_info_struct(png);
			png_infop end  = png_create_info_struct(png);
            if (png && info && end) {
				success = PNGReadHeader(png, info);
			}
			if (success) {
                width  = png_get_image_width(png, info);
                height = png_get_image_height(png, info);
                size_t pixelSize = width * height * BYTES_PER_PIXEL;
                if (pixelSize != gbaBackground->imageSize) {
                    // 释放旧的像素缓存
                    mappedMemoryFree(gbaBackground->image, gbaBackground->imageSize);
                    // 清空指针，等待重新分配
                    gbaBackground->image = NULL;
                }
                // 像素缓冲区指针
                color_t* pixels = gbaBackground->image;
                // 若当前尚未分配像素缓冲区
                if (!pixels) {
                    // 使用匿名内存映射分配像素缓存
                    pixels = anonymousMemoryMap(pixelSize);
                    // 保存到背景结构中
                    gbaBackground->image = pixels;
                    gbaBackground->imageSize = pixelSize;
                }
				else
				{
                    isSame = true;
				}

                if (pixels) {
					// 读取 PNG 像素数据到 pixels 缓冲区
					success = success &&
						PNGReadPixels(png, info, pixels, width, height, width);
					// 读取 PNG 尾信息
					success = success &&
						PNGReadFooter(png, end);

                }
            }
            // 关闭 PNG 读取并释放相关结构
            PNGReadClose(png, info, end);
        }
        // 如果 VFile 存在，关闭文件
        if (vf) {
            vf->close(vf);
        }

        if (success) {
            gbaBackground->p->drawBKImage(
                gbaBackground->p,
                gbaBackground->image,
                width,
                height,
                false,
                isSame
            );
        }
    }

}


void bk_init_mask_texture(const char* filepath, int maskType){
    char* maskpath = bk_util_str_concatenate("sdmc:", filepath);
    
    struct VFile* vf = bk_util_open_png(maskpath, O_RDONLY);
    bool success = false;  // 初始化成功标志
    if(pixels)
    {
        free(pixels);
        pixels = NULL;
    }
    unsigned width = 0, height = 0;  // 初始化宽高
    
    if (vf) {
        free(maskpath);
        
        png_structp png = PNGReadOpen(vf, PNG_HEADER_BYTES);
        png_infop info = png_create_info_struct(png);
        png_infop end  = png_create_info_struct(png);
        
        if (png && info && end) {
            success = PNGReadHeader(png, info);
        }
        
        if (success) {
            
            width  = png_get_image_width(png, info);
            height = png_get_image_height(png, info);
            int type = png_get_color_type(png, info);
            int depth = png_get_bit_depth(png, info);
            if (success) {
                // 读取 PNG 像素数据到 pixels 缓冲区
                switch (type) {
                    case PNG_COLOR_TYPE_RGB:
                        if (depth != 8) {
                            break;
                        }
                        pixels = anonymousMemoryMap(width * height * 4);
                        success = success && PNGReadPixels(png, info, pixels, width, height, width);
                        break;
                    case PNG_COLOR_TYPE_RGBA:
                        if (depth != 8) {
                            break;
                        }
                        pixels = anonymousMemoryMap(width * height * BYTES_PER_PIXEL);
                        success = success && PNGReadPixelsA(png, info, pixels, width, height, width);
                        break;
                    default:
                        break;
                }
                // 读取 PNG 尾信息
                success = success &&
                    PNGReadFooter(png, end);
            } else {
                success = false;
            }
        } else {
            printf("错误：PNG头信息读取失败\n");  // 头信息读取失败
        }
        
        // 关闭 PNG 读取并释放相关结构
        PNGReadClose(png, info, end);
    } else {
        printf("错误：无法打开遮罩纹理文件\n");  // 文件打开失败
    }
    
    if (vf) {
        vf->close(vf);
    }
    
    if (success) {
        glBindTexture(GL_TEXTURE_2D, maskType == 0 ? bkMaskTexGBA : bkMaskTexGBC);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    } else {
        printf("错误：遮罩纹理加载失败: %s\n", filepath);  // 加载失败
    }
    
    BK_GLOBAL_INT_SET(maskType == 0 ? BK_META_MASK_STATUS_GBA : BK_META_MASK_STATUS_GBC, success);
}