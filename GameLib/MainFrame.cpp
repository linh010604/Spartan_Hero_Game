/**
 * @file MainFrame.cpp
 * @author Roshni Kaur
 */


#include "pch.h"
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
    mGameView = new GameView();
    mGameView->Initialize(this);

    // Add it to the sizer
    sizer->Add(mGameView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();
}

