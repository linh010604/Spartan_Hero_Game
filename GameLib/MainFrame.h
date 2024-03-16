/**
 * @file MainFrame.h
 * @author Linh Nguyen
 *
 * File for MainFrame Class
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

#include "Game.h"

// Forward reference
class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// View class for our Game
    GameView *mGameView;


    void OnAbout(wxCommandEvent& event); // Declare the OnAbout method
    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent &event);

public:
    void Initialize(ma_engine *PEngine);

};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
