/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "GameView.h"
#include <wx/dcbuffer.h>

wxBEGIN_EVENT_TABLE(GameView, wxWindow)
        EVT_PAINT(GameView::OnPaint)
        EVT_LEFT_DOWN(GameView::OnLeftDown)
wxEND_EVENT_TABLE()

GameView::GameView(wxFrame* parent)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE) { // Modified to include wxFULL_REPAINT_ON_RESIZE
    // Constructor
}



void GameView::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

void GameView::OnLeftDown(wxMouseEvent &event) {
    mGame.OnLeftDown(event.GetX(), event.GetY());
}

GameView::GameView() {

}

void GameView::Initialize(wxFrame* parent)
{
}