/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include "GameView.h"
#include <wx/dcbuffer.h>



wxBEGIN_EVENT_TABLE(GameView, wxWindow)
EVT_PAINT(GameView::OnPaint)
EVT_LEFT_DOWN(GameView::OnLeftDown)
wxEND_EVENT_TABLE()

GameView::GameView(wxFrame* parent)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE) {
    // Constructor
}

void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Clear the image to black
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto gc =
        std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());


}

void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());
}