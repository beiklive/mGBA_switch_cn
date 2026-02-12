#pragma once

#include "core/common.h"

namespace beiklive
{

    class OpenGLManager
    {
    public:
        OpenGLManager();
        ~OpenGLManager();
        // 公共接口
        void initBackgroundTexture(Vector2f ScreenHint);
        void initMenuTexture(Vector2f ScreenHint);
        void initFontTexture(Vector2f ScreenHint);
        
        // 获取纹理ID
        GLuint getBackgroundTexture() const { return background_tex; }
        GLuint getBackgroundProgram() const { return background_program; }
        GLuint getMenuTexture() const { return menu_tex; }
        GLuint getFontTexture() const { return font_tex; }

    private:    
        GLuint createEmptyTexture(Vector2f size);

        GLuint menu_tex; // 菜单纹理
        GLuint background_tex; // 背景纹理
        GLuint font_tex; // 字体纹理

        GLuint background_program; // 背景渲染程序


    };





} // namespace beiklive
