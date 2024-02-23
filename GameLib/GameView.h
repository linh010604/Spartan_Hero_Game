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

    /// The game
    Game mGame;

public:
    /**
    * Initialize the aquarium view class.
    * @param mainFrame The parent window for this class
    */
    void Initialize(wxFrame *parent);
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

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H
