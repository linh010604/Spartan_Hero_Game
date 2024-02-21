/**
 * @file GameApp.cpp
 * @author Nicolas Roberts
 */

#include "pch.h"

#include "MainFrame.h"
#include "GameApp.h"

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
    frame->Initialize();

    frame->SetFocus();
    frame->Raise();
    frame->Show(true);

    return true;
}