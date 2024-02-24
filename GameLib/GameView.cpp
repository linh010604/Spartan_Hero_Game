/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 */

#include "pch.h"

#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>

#include "GameView.h"
#include "ids.h"
#include "Meter.h"

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

    // Allows ability to paint on background
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL0);

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

void GameView::OnLevelOption(wxCommandEvent& event)
{
    wxString filename;

    switch(event.GetId())
    {
        case IDM_LEVEL0:
            filename = "levels/level0.xml";
            mGame.Load(filename);
            Refresh();
            break;

    }

}