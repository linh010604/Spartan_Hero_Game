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

class GameView : public wxWindow
{
private:

    /// The game
    Game mGame;


public:
    void Initialize(wxFrame *mainFrame);
    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);





wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H
