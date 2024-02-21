/**
 * @file GameView.h
 * @author Angelina Jolie Daoud
 *
 *
 */

#ifndef PROJECT1_GAMELIB_GAMEVIEW_H
#define PROJECT1_GAMELIB_GAMEVIEW_H


#include <wx/wx.h>
#include <wx/graphics.h>
#include "Game.h"
#include "MainFrame.h"

class GameView : public wxWindow
{
private:



public:
    GameView();
    GameView(wxFrame* parent);

    void Initialize(wxFrame* parent);

    Game mGame; // Game instance

    void OnPaint(wxPaintEvent& event);
    void OnLeftDown(wxMouseEvent& event);






wxDECLARE_EVENT_TABLE()



;};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H
