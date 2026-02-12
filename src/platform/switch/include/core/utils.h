#pragma once

#include "common.h"


namespace beiklive
{
    namespace utils
    {
        unsigned char* loadImage(const char* filename, int* width, int* height, int* channels, GLenum* format);
    } // namespace utils
} // namespace beiklive
