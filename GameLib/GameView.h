/**
 * @file GameView.h
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 *
 * File for view class
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

    void Initialize(wxFrame *mainFrame);

    void OnPaint(wxPaintEvent& event);

    void OnLeftDown(wxMouseEvent& event);

    void OnLevelOption(wxCommandEvent& event);

/**
* Declares event table
*/
wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H

