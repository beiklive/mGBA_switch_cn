#pragma once

#include "core/common.h"


class EglManager {
public:
    EglManager() = default;
    ~EglManager() = default;


    bool init();
    void deinit();

    void swapBuffers();

private:
    EGLDisplay s_display;       // EGL显示器
    EGLContext s_context;       // OpenGL上下文
    EGLSurface s_surface;       // 渲染表面


};