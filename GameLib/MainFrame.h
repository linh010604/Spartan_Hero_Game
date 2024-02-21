/**
 * @file MainFrame.h
 * @author Roshni Kaur
 *
 *
 */
#include <wx/wxprec.h>
#include <wx/wx.h>
#ifndef PROJECT1_GAMELIB_MAINFRAME_H
#define PROJECT1_GAMELIB_MAINFRAME_H

#include "GameView.h"

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
