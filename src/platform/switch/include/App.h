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



private:
	void Initialize();



    NWindow* window;
	EglManager* eglManager;
	beiklive::OpenGLManager* glManager;
	bool running;
    u32 vwidth, vheight;
    u8 vmode;
};
} // namespace beiklive


