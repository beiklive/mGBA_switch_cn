#pragma once

#include <switch.h>
#include "core/common.h"
#include "EglManager.h"
#include "OpenGLManager.h"

namespace beiklive
{
class App {
public:
    App();
    ~App();

    void RunLoop();
    void SetScreenSize(u32 width, u32 height);
    bool CheckScreenMode();
    Vector2f GetScreenSize();

    // 供 Plutonium 布局调用的切换方法
    void ShowUIMode(bool show);

private:
    void Initialize();

    NWindow* window;
    EglManager* eglManager;
    beiklive::OpenGLManager* glManager;


    bool uiVisible;      // 当前是否显示 UI 菜单
    bool running;
    u32 vwidth, vheight;
    u8 vmode;
};
}