#include "core/utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "core/stb_image.h"

namespace beiklive::utils
{
    unsigned char* loadImage(const char* filename, int* width, int* height, int* channels, GLenum* format)
    {
        int m_width, m_height, m_nrChannels;
        GLenum m_format = GL_RGB;

        stbi_set_flip_vertically_on_load(0);
        unsigned char* data = stbi_load(filename, &m_width, &m_height, &m_nrChannels, 0);
        if (!data) {
            spdlog::error("Failed to load image: {}", filename);
            return nullptr;
        }
        if (m_nrChannels == 4) *format = GL_RGBA;
        else if (m_nrChannels == 1) *format = GL_RED;
        *width = m_width;
        *height = m_height;
        *channels = m_nrChannels;
        return data;
    }
} // namespace beiklive

