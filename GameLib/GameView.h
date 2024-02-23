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

public:
    /**
    * Initialize the game view class.
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



/**
* Declares event table
*/
wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H

