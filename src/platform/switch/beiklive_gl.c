#include <beiklive/beiklive.h>

GLuint bkTex;

bool bk_opengl_init(void)
{
	// BKMARK 背景绘制纹理
	glGenTextures(1, &bkTex);
	glBindTexture(GL_TEXTURE_2D, bkTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1280, 720, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

}

void bk_opengl_deinit(void) { 
    glDeleteTextures(1, &bkTex);
}

void _bk_util_draw_game_logo(struct GUIBackground* background, void* title)
{
    struct mGUIBackground* gbaBackground = (struct mGUIBackground*) background;
    bool success;
    unsigned width, height;
    bool isSame = false;
    if(gbaBackground->p->drawBKImage)
    {
        char* logoPath =
		    bk_util_str_concatenate_multiple(
				4,
				BK_LOGO_BASE_PATH,
				"/",
				bk_util_remove_extension(title),
				".png"
			);
		struct VFile* vf = bk_util_open_png(logoPath, O_RDONLY);

		if (vf) {
            if (logoPath) {
                free(logoPath);
            }

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
            int screenWidth = gbaBackground->p->params.width;  
            int screenHeight = gbaBackground->p->params.height;
            int targetX = 0;
            int targetY = screenHeight;
            int targetWidth = screenWidth;
            int targetHeight = screenHeight;

            gbaBackground->p->drawBKImage(
                gbaBackground->p,
                gbaBackground->image,
                width,
                height,
                false,
                targetX,
                targetY,
                screenWidth,
                screenHeight,
                isSame
            );
        }
    }

}