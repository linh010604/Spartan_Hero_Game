/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 */

#include "pch.h"
#include "ids.h"

#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>

#include "GameView.h"

using namespace std;

void GameView::Initialize(wxFrame* parent) {
    Create(parent, wxID_ANY);

    // Determine where the images are stored
    //auto standardPaths = wxStandardPaths::Get();
    wxStandardPaths& standardPaths = wxStandardPaths::Get();
    std::wstring resourcesDir = standardPaths.GetResourcesDir().ToStdWstring();
    mGame.SetImagesDirectory(resourcesDir);

    // Allows ability to paint on background
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Binds paint function with event
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);
    // Binds left down function with event
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
    // On left down mouse click gets X and Y values
    mGame.OnLeftDown(event.GetX(), event.GetY());
}

