#pragma once

#include <switch.h>
#include "core/common.h"
#include "EglManager.h"
namespace beiklive
{
class App {
public:
	App();
	~App();

	void RunLoop();

private:
	void Initialize();

	EglManager* eglManager;
	bool running;
    u32 vwidth, vheight;
    u8 vmode;
};
} // namespace beiklive


