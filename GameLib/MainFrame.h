/**
 * @file MainFrame.h
 * @author thaol
 *
 * File for MainFrame class
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

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

public:
    void Initialize();

};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
