/**
 * @file MainFrame.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

class GameView;

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame {
private:

    /// View class for our aquarium
    GameView *mGameView;

    /**
     * Handles About item event from menu.
     * Method displays a dialog showing info about application.
     * @param event The event object associated with the About action.
     */
    void OnAbout(wxCommandEvent& event); // Declare the OnAbout method
    void OnExit(wxCommandEvent& event);

public:
    void Initialize();

};

#endif //PROJECT1_GAMELIB_MAINFRAME_H
