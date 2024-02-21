/**
 * @file MainFrame.cpp
 * @author thaol
 */

#include "pch.h"
#include "MainFrame.h"
#include "GameView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Game", wxDefaultPosition, wxSize(1000, 800));

    auto sizer = new wxBoxSizer(wxVERTICAL);

    mGameView = new GameView();
    mGameView->Initialize(this);

    sizer->Add(mGameView, 1, wxEXPAND | wxALL);

    SetSizer(sizer);
    Layout();

}