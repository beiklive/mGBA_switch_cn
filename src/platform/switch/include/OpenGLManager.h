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
        void deleteGL(GLES2Shader * gl);
        
        void initPreprocessShader(Vector2f ScreenHint);
        


        GLES2PreprocessShader* getPreprocessShader() const { return preprocess_gl; }

    private:    
        // 初始化预处理着色器
        GLuint createEmptyTexture(Vector2f size);
        void initShader(GLES2PreprocessShader * gl, ShaderType type);
        GLuint GetProgram(ShaderType type);

        GLES2PreprocessShader * preprocess_gl;

        // GLuint menu_tex; // 菜单纹理
        // GLuint background_tex; // 背景纹理
        // GLuint font_tex; // 字体纹理

        // GLuint background_program; // 背景渲染程序


    };





} // namespace beiklive
