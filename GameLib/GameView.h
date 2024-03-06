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
    /**
   * Paint event, draws the window.
   * @param event Paint event object
   */
    void OnPaint(wxPaintEvent& event);

    void OnTimer(wxTimerEvent& event);

    /// The timer that allows for animation
    wxTimer mTimer;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// The game
    Game mGame;

    bool mDisplayLevelNotice = false;
    wxStopWatch mLevelNoticeStopWatch;
    int mCurrentLevel = 0;

public:

    /**
     * Constructor
     * @param audioEngine The audio engine to use
     */
    GameView(ma_engine *audioEngine);

    void Initialize(wxFrame *mainFrame);

    /**
    * Handle the left mouse button down event
    * @param event
    */
    void OnLeftDown(wxMouseEvent& event);

    void OnLevelOption(wxCommandEvent& event);

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}

    /// Method to display level notice
    void DisplayLevelNotice(int level);

/**
* Declares event table
*/
wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H

