/**
 * @file MainFrame.cpp
 * @author thaol
 */

#include "pch.h"
#include "ids.h"
#include "MainFrame.h"
#include "GameView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Spartan Hero",
           wxDefaultPosition,  wxSize( 1000,800 ));



    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto gameView = new GameView();
    gameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(gameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    CreateStatusBar();

    auto menuBar = new wxMenuBar( );

    auto fileMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto levelMenu = new wxMenu();

    menuBar->Append(fileMenu, L"&File" );
    menuBar->Append(levelMenu, L"&Level" );
    menuBar->Append(helpMenu, L"&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit this program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");
    levelMenu->Append(IDM_LEVEL0, L"&Level 0");
    levelMenu->Append(IDM_LEVEL1, L"&Level 1");
    levelMenu->Append(IDM_LEVEL2, L"&Level 2");
    levelMenu->Append(IDM_LEVEL3, L"&Level 3");
    levelMenu->Append(IDM_AUTOPLAY, L"&Autoplay");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    SetMenuBar( menuBar );
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
                 L"About Saprtan Hero",
                 wxOK,
                 this);
}
