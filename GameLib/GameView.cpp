/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 */

#include "pch.h"

#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>

//#include "Game.h"
#include "GameView.h"

using namespace std;

/**
* The event table that connects window events
*/
wxBEGIN_EVENT_TABLE(GameView, wxWindow)
EVT_PAINT(GameView::OnPaint)
EVT_LEFT_DOWN(GameView::OnLeftDown)
wxEND_EVENT_TABLE()

void GameView::Initialize(wxFrame *mainFrame) {
    Create(mainFrame, wxID_ANY);

    // Determine where the images are stored
    //auto standardPaths = wxStandardPaths::Get();
    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
    mGame.SetImagesDirectory(resourcesDir);

    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);
}

void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    gc->SetBrush(*wxBLACK_BRUSH);
    wxRect rect = GetRect();
    gc->DrawRectangle(0, 0, rect.GetWidth(), rect.GetHeight());


    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
}

void GameView::OnLeftDown(wxMouseEvent &event)
{
    mGame.OnLeftDown(event.GetX(), event.GetY());
}