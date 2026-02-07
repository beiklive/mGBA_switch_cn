#include <beiklive/beiklive.h>


bool bk_rewind_init(struct mGUIRunner* runner)
{
    if (!runner->rewindEnabled) {
        return false;
    }
    
    if (runner->rewind.currentState) {
        mCoreRewindContextDeinit(&runner->rewind);
    }
    
    mCoreRewindContextInit(&runner->rewind, runner->rewindBufferSize, false);
    runner->rewindFrames = 0;
    
    return true;
}

bool bk_performRewind(struct mGUIRunner* runner) {
    if (!runner->rewindEnabled || !runner->rewind.currentState) {
        return false;
    }
    
    // 执行倒带恢复
    bool success = mCoreRewindRestore(&runner->rewind, runner->core);
    
    if (success) {
        // 倒带成功后强制重绘
		runner->core->runFrame(runner->core);
        if (runner->drawFrame) {
            runner->params.drawStart();
            runner->drawFrame(runner, false);

			bk_draw_mask(runner);




            runner->params.drawEnd();
        }
        
        return true;
    } else {
        runner->rewinding = false;
        runner->rewindPaused = true;
        return false;
    }
}

void bk_saveRewindState(struct mGUIRunner* runner) {
    if (!runner->rewindEnabled || !runner->rewind.currentState || runner->rewinding) {
        return;
    }
    
    // 根据间隔保存状态
    if (runner->rewindFrames % runner->rewindSaveInterval == 0) {
        mCoreRewindAppend(&runner->rewind, runner->core);
    }
    runner->rewindFrames++;
}

void bk_rewind_deinit(struct mGUIRunner* runner)
{
    if (runner->rewind.currentState) {
        mCoreRewindContextDeinit(&runner->rewind);
    }
}


// void bk_updateRewindStatus(struct mGUIRunner* runner, struct GUIFont* font, 
//                                 int drawFps, int showOSD) {
//     if (!runner->rewindEnabled || !runner->rewinding) {
//         return;
//     }
    
//     // 计算倒带状态信息
//     float fillPercent = 0.0f;
//     if (runner->rewindBufferSize > 0) {
//         fillPercent = (float)runner->rewind.size / runner->rewindBufferSize * 100.0f;
//     }
    
//     // 显示倒带状态
//     if (runner->rewindPaused) {
//         GUIFontPrintf(font, 0, GUIFontHeight(font) * 2, GUI_ALIGN_LEFT, 
//                     0x7FFF0000, "倒带暂停");
//     } else {
//         GUIFontPrintf(font, 0, GUIFontHeight(font) * 2, GUI_ALIGN_LEFT, 
//                     0x7FFF0000, "倒带中 %.1f%%", fillPercent);
//     }
// }