/**
 * @file GameView.h
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 *
 */

#ifndef PROJECT1_GAMELIB_GAMEVIEW_H
#define PROJECT1_GAMELIB_GAMEVIEW_H

#include "Game.h"

/**
 * View class for our game
 */
class GameView : public wxWindow
{
private:

    /// The timer that allows for animation
    wxTimer mTimer;

    ma_engine *mAudioEngine;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    /// The game
    Game mGame;

    bool mDisplayLevelNotice = true;
    wxStopWatch mLevelNoticeStopWatch;
    int mCurrentLevel = 1;

public:

    /**
     * Constructor
     * @param audioEngine The audio engine to use
     */
    GameView(ma_engine *audioEngine);

    /**
     * Paint event, draws the window.
     * @param event Paint event object
     */
    void OnPaint(wxPaintEvent& event);

    void Initialize(wxFrame *mainFrame);

    /// Method to display level notice
    void DisplayLevelNotice(int level);

    /**
     * Stop the timer so the window can close
     */
    void Stop() {mTimer.Stop();}

    void OnLevelOption(wxCommandEvent& event);

    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void OnTimer(wxTimerEvent& event);

/**
* Declares event table
*/
wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H

