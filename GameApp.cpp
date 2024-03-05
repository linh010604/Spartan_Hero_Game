/**
 * @file GameApp.cpp
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "GameApp.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "MainFrame.h"

/**
 * Initialize the application.
 * @return
 */
bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize(&mAudioEngine);

    frame->Show(true);

    // Initialize the audio engine
    auto result = ma_engine_init(nullptr, &mAudioEngine);
    if (result != MA_SUCCESS)
    {
        wxString msg;
        msg.Printf(L"Unable to initialize miniaudio engine - %d", result);
        wxMessageBox(msg, wxT("miniaudio failure"), wxICON_ERROR);
        return false;
    }

    // Continue with your initialization logic

    return true;
}

int GameApp::OnExit()
{
    ma_engine_uninit(&mAudioEngine);

    // Continue with your exit logic

    return wxAppBase::OnExit();
}