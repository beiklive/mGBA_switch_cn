#include "App.h"
namespace beiklive
{
App::App(): eglManager(new EglManager()), running(false), vwidth(0), vheight(0)
{ 
    Initialize();

}

App::~App() {
	eglManager->deinit();
    delete eglManager;
}

 void App::Initialize() {
    TimeType __nx_time_type = TimeType_UserSystemClock;

	NWindow* window = nwindowGetDefault();
	nwindowSetDimensions(window, 1920, 1080);

	// 初始化显示模式
	vmode = appletGetOperationMode();
	if (vmode == AppletOperationMode_Console) {
		vwidth = 1920;
		vheight = 1080;
	} else {
		vwidth = 1280;
		vheight = 720;
	}
	nwindowSetCrop(window, 0, 0, vwidth, vheight);
	socketInitializeDefault();   // 网络套接字
	nxlinkStdio();               // 标准IO重定向
    romfsInit();                 // 只读文件系统
	audoutInitialize();          // 音频输出
	psmInitialize();             // 电源状态管理
    eglManager->init();          // EGL初始化
    running = true;
}

void App::RunLoop() { 
    while(running){

        spdlog::info("Welcome to spdlog!");

        eglManager->swapBuffers();
    }
    return;
}

}