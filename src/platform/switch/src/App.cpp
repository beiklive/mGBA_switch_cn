#include "App.h"
namespace beiklive
{
App::App(): 
        eglManager(new EglManager()), 
        glManager(new beiklive::OpenGLManager()), 
        running(false), 
        vwidth(0), 
        vheight(0)
{ 
    Initialize();

}

App::~App() {
	eglManager->deinit();
    delete eglManager;

	psmExit();
	audoutExit();
	romfsExit();
	socketExit();

}

 void App::Initialize() {
    TimeType __nx_time_type = TimeType_UserSystemClock;

	window = nwindowGetDefault();
	nwindowSetDimensions(window, 1920, 1080);

	// 初始化显示模式
	vmode = appletGetOperationMode();
	if (vmode == AppletOperationMode_Console) {
        SetScreenSize(1920, 1080);
	} else {
        SetScreenSize(1280, 720);
    }

	socketInitializeDefault();   // 网络套接字
	nxlinkStdio();               // 标准IO重定向
    romfsInit();                 // 只读文件系统
	audoutInitialize();          // 音频输出
	psmInitialize();             // 电源状态管理
    eglManager->init();          // EGL初始化

    glManager->initBackgroundGL(GetScreenSize());
    glManager->initMenuTexture(GetScreenSize());
    glManager->initFontTexture(GetScreenSize());

}

void App::RunLoop() { 
    running = true;
    while(appletMainLoop()){
        // 清空颜色缓冲
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, glManager->getBackgroundTexture());
        
        glViewport(0, 1080 - vheight, vwidth, vheight);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUseProgram(glManager->getBackgroundProgram());

        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

        glBindVertexArray(0);
        glUseProgram(0);
        glDisable(GL_BLEND);


        eglManager->swapBuffers();
        CheckScreenMode();
    }
    return;
}

void App::SetScreenSize(u32 width, u32 height) { 
    vwidth = width;
    vheight = height;
    nwindowSetCrop(window, 0, 0, vwidth, vheight);
}

bool App::CheckScreenMode() {
    u8 newMode = appletGetOperationMode();
	if (newMode != vmode) {
        vmode = newMode;
        if (vmode == AppletOperationMode_Console) {
            SetScreenSize(1920, 1080);
        } else {
            SetScreenSize(1280, 720);
        }
    }
    return appletMainLoop();
}

Vector2f App::GetScreenSize() {
	return Vector2f(vwidth, vheight);
}

} // namespace beiklive