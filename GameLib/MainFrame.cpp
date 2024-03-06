/**
 * @file MainFrame.cpp
 * @author thaol
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"
#include "ids.h"

/**
 * Initialize the MainFrame window.
 * @param PEngine The audio engine for miniaudio
 */
void MainFrame::Initialize(ma_engine *PEngine)
{
    Create(nullptr, wxID_ANY, L"Spartan Hero",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView(PEngine);
    gameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level");
    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVEL0, L"Level 0",L"Select Level 0");
    levelMenu->Append(IDM_LEVEL1, L"Level 1",L"Select Level 1");
    levelMenu->Append(IDM_LEVEL2, L"Level 2",L"Select Level 2");
    levelMenu->Append(IDM_LEVEL3, L"Level 3", L"Select Level 3");
    levelMenu->AppendSeparator();
    levelMenu->Append(IDM_AUTOPLAY, L"Autoplay", L"Select Autoplay");

    SetMenuBar( menuBar );
    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}


void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox(L"Welcome to the Game!",
                 L"About Spartan Hero",
                 wxOK,
                 this);
}

/**
 * Handle a close event. Stop the animation and destroy this window.
 * @param event The Close event
 */
void MainFrame::OnClose(wxCloseEvent& event)
{
    mGameView->Stop();
    Destroy();
}
