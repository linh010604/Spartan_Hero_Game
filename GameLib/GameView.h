/**
 * @file GameView.h
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 *
 */

#ifndef PROJECT1_GAMELIB_GAMEVIEW_H
#define PROJECT1_GAMELIB_GAMEVIEW_H


#include <wx/wx.h>
#include <wx/graphics.h>
#include "Game.h"
/**
 * View class for our game
 */
class GameView : public wxWindow
{
private:
    //GameView(wxFrame* parent);

    /// The game
    Game mGame;

    void AddTileMenuOption(wxFrame *mainFrame, wxMenu *menu, int id, std::wstring text);

public:
    /**
    * Initialize the aquarium view class.
    * @param mainFrame The parent window for this class
    */
    void Initialize(wxFrame *mainFrame);
    /**
    * Paint event, draws the window.
    * @param event Paint event object
    */
    void OnPaint(wxPaintEvent& event);
    /**
    * Handle the left mouse button down event
    * @param event
    */
    void OnLeftDown(wxMouseEvent& event);

    void AddMenus(wxFrame *mainFrame, wxMenuBar *menuBar);


};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H
