/**
 * @file GameView.h
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 *
 * File for the Game View class
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

    /// The audio engine for miniaudio
    ma_engine *mAudioEngine;

    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

    long mClosingTime = 0 ; ///< The time displaying closing message

    /// The game
    Game mGame;

    bool mDisplayLevelNotice = true; ///< bool checking if the notice has been display

    wxStopWatch mLevelNoticeStopWatch; ///< Stopwatch used to get time for Notice display

    int mCurrentLevel = 1; ///< Current level of the game

    bool mAutoPlay = false; ///< Autoplay mode of the game

public:

    /**
     * Constructor
     * @param audioEngine The audio engine to use
     */
    GameView(ma_engine *audioEngine);

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
    void Sequence();
    void OnAutoPlayMode(wxCommandEvent& event);
    void DisplayStar(std::shared_ptr<wxGraphicsContext> gc);

/**
* Declares event table
*/
wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_GAMELIB_GAMEVIEW_H


