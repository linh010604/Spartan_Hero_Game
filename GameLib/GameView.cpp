/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 */

#include "pch.h"

#include "GameView.h"
#include "Sound.h"
#include "ids.h"

#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>
#include <thread>
#include <chrono>

using namespace std;


/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(192, 252, 207);


/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
* The event table that connects window events
*/
wxBEGIN_EVENT_TABLE(GameView, wxWindow)
        EVT_PAINT(GameView::OnPaint)
wxEND_EVENT_TABLE()

GameView::GameView(ma_engine *audioEngine) : mGame(audioEngine), mAudioEngine(audioEngine)
{
}

/**
 * Initialize the game view class.
 * @param mainFrame The parent window for this class
 */
void GameView::Initialize(wxFrame *mainFrame) {
    Create(mainFrame, wxID_ANY);

    // Allows ability to paint on background
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Binds paint function with event
    Bind(wxEVT_PAINT, &GameView::OnPaint, this);

    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL0);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL1);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL2);
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnLevelOption, this, IDM_LEVEL3);

    mGame.Load(L"levels/level1.xml");
    Refresh();

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    mainFrame->Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mStopWatch.Start();

}

void GameView::OnPaint(wxPaintEvent& event)
{
    // Create a double-buffered display context
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
    mGame.Update(elapsed);

    if (mDisplayLevelNotice && mLevelNoticeStopWatch.Time() < LevelNoticeDuration * 1000) {
        wxString noticeText = wxString::Format("Level %d Begin", mCurrentLevel);
        wxFont font(NoticeSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gc->SetFont(font, LevelNoticeColor);

        // Measure text size
        double textWidth, textHeight;
        gc->GetTextExtent(noticeText, &textWidth, &textHeight, nullptr, nullptr);

        // Calculate positions to center the text
        double xPos = (mGame.GetWidth() - textWidth) / 2;
        double yPos = (mGame.GetHeight() - textHeight) / 2;

        gc->DrawText(noticeText, xPos, yPos);
    } else {
        mDisplayLevelNotice = false;
    }

    // Restores state of graphics
    gc->PopState();

}

void GameView::DisplayLevelNotice(int level) {
    mCurrentLevel = level;
    mDisplayLevelNotice = true;
    mLevelNoticeStopWatch.Start();
}

/**
 * Handle level choosing event
 * @param event Command event
 */
void GameView::OnLevelOption(wxCommandEvent& event)
{
    wxString filename;
    int levelNumber = 0;

    switch(event.GetId()) {
        case IDM_LEVEL0:
            filename = L"levels/level0.xml";
            levelNumber = 0;
            break;
        case IDM_LEVEL1:
            filename = L"levels/level1.xml";
            levelNumber = 1;
            break;
        case IDM_LEVEL2:
            filename = L"levels/level2.xml";
            levelNumber = 2;
            break;
        case IDM_LEVEL3:
            filename = L"levels/level3.xml";
            levelNumber = 3;
            break;
    }

    mStopWatch.Start();
    mTime = 0;
    mGame = Game(mAudioEngine);
    mGame.Load(filename);
    Refresh();
    DisplayLevelNotice(levelNumber);

}

/**
 * Handle a key press event
 * @param event Keypress event
 */
void GameView::OnKeyDown(wxKeyEvent& event)
{
    wxChar key = event.GetKeyCode();
    // A = 65, S = 83, D = 68, F = 70
    // J = 74, K = 75, L = 76, ; = 59
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mGame.PressKey(key, elapsed);
    mGame.Update(elapsed);

//    sound.SetVolume(0.5);
//    sound.LoadSound(mGame.GetAudioEngine());
//
//    sound.PlaySound();
//    std::this_thread::sleep_for(std::chrono::seconds(1)); //pauses for 1 seconds
//    sound.PlayEnd();
}

/**
 * Handle a key release event
 * @param event ItemTrackLine release event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
}

/**
 * Handle timer events
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}