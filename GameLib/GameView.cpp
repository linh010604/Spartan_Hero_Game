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

void GameView::Initialize(wxFrame *mainFrame) {
    Create(mainFrame, wxID_ANY);

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

/**
 * Add menus specific to the view
 * @param mainFrame The main frame that owns the menu bar
 * @param menuBar The menu bar to add menus to
 */
void GameView::AddMenus(wxFrame* mainFrame, wxMenuBar *menuBar)
{
    auto levelMenu = new wxMenu();

    //
    // Level menu options
    //
    AddTileMenuOption(mainFrame, levelMenu, IDM_LEVEL0, L"&Level 0");
    AddTileMenuOption(mainFrame, levelMenu, IDM_LEVEL1, L"&Level 1");
    AddTileMenuOption(mainFrame, levelMenu, IDM_LEVEL2, L"&Level 2");
    AddTileMenuOption(mainFrame, levelMenu, IDM_LEVEL3, L"&Level 3");
    levelMenu->AppendSeparator();
    AddTileMenuOption(mainFrame, levelMenu, IDM_AUTOPLAY, L"&Autoplay");

    menuBar->Append(levelMenu, L"Level" );

}

/**
 * Append an option to a menu and bind it to the function CityView::OnAddTileMenuOption
 *
 * All of the menu options to add a tile use the same menu handler, which uses
 * a switch based on the ID to determine which option to make. This code cuts the
 * number of lines of code in CityView::AddMenus by about half.
 *
 * @param mainFrame The MainFrame object that owns the menu
 * @param menu The Menu we are adding the option to
 * @param id The Menu option ID
 * @param text Text for the menu option
 * @param help Help for the menu option
 */
void GameView::AddTileMenuOption(wxFrame *mainFrame, wxMenu *menu, int id, std::wstring text)
{
    menu->Append(id, text);
    //mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &CityView::OnAddTileMenuOption, this, id);
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