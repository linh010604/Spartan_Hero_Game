/**
 * @file MainFrame.h
 * @author Roshni Kaur
 *
 *
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

#include <wx/filehistory.h>
#include <wx/config.h>

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:
    /// View class for our game
    GameView *mGameView;

    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent&);
    void OnClose(wxCloseEvent &event);

    /// Application assocated configurations
    wxConfig mConfig;

public:
    void Initialize();

};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
