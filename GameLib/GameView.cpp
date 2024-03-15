/**
 * @file GameView.cpp
 * @author Angelina Jolie Daoud
 * @author Linh Nguyen
 */

#include "pch.h"

#include "GameView.h"
#include "Sound.h"
#include "ids.h"
#include "Game.h"

#include <wx/stdpaths.h>
#include <wx/dcbuffer.h>
#include <thread>

using namespace std;


/// Level notices duration in seconds
const double LevelNoticeDuration = 2.0;

/// Size of notices displayed on screen in virtual pixels
const int NoticeSize = 100;

/// Color to draw the level notices
const auto LevelNoticeColor = wxColour(192, 252, 207);

const int FullPoint = 10;

/// Frame duration in milliseconds
const int FrameDuration = 30;

const wstring threestars = L"stars/threestar.png";

const wstring twostars = L"stars/twostar.png";

const wstring onestar = L"stars/onestar.png";

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
    mainFrame->Bind(wxEVT_COMMAND_MENU_SELECTED, &GameView::OnAutoPlayMode, this, IDM_AUTOPLAY);

    mGame.Load(L"levels/level1.xml");
    Refresh();

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

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
    } else if (mDisplayLevelNotice){
        mDisplayLevelNotice = false;
    }

    if (mGame.GetState() == Game::GameState::Closing){
        if (mClosingTime == 0){
            mClosingTime = mStopWatch.Time();
        }
        if ( mStopWatch.Time() - mClosingTime <= LevelNoticeDuration*1000){
            wxString noticeText = wxString::Format("Level %d Complete", mCurrentLevel);
            wxFont font(NoticeSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
            gc->SetFont(font, LevelNoticeColor);

            // Measure text size
            double textWidth, textHeight;
            gc->GetTextExtent(noticeText, &textWidth, &textHeight, nullptr, nullptr);

            // Calculate positions to center the text
            double xPos = (mGame.GetWidth() - textWidth) / 2;
            double yPos = (mGame.GetHeight() - textHeight) / 2;

            gc->DrawText(noticeText, xPos, yPos);
        }
        else if  (mStopWatch.Time() - mClosingTime >= 2*LevelNoticeDuration*1000)
        {
            mCurrentLevel = (mCurrentLevel + 1) % 4;
            Sequence();
        }
        else if (mStopWatch.Time() - mClosingTime < 2*LevelNoticeDuration*1000 && mStopWatch.Time() - mClosingTime > LevelNoticeDuration*1000)
        {
            DisplayStar(gc);
        }

    }

    // Restores state of graphics
    gc->PopState();

    mGame.Update(elapsed);

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
    mGame.UpdateAutoPlayMode(mAutoPlay);
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
    mGame.PressKey(key);

}

/**
 * Handle a key release event
 * @param event ItemTrackLine release event
 */
void GameView::OnKeyUp(wxKeyEvent& event)
{
    wxChar key = event.GetKeyCode();
    // A = 65, S = 83, D = 68, F = 70
    // J = 74, K = 75, L = 76, ; = 59
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    mGame.KeyUp(key);
}

/**
 * Handle timer events
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent& event)
{
    Refresh();
}

void GameView::Sequence()
{
    wxString filename;
    int levelNumber = 0;
    switch(mCurrentLevel) {
        case 0:
            filename = L"levels/level0.xml";
            levelNumber = 0;
            break;
        case 1:
            filename = L"levels/level1.xml";
            levelNumber = 1;
            break;
        case 2:
            filename = L"levels/level2.xml";
            levelNumber = 2;
            break;
        case 3:
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
    mGame.UpdateAutoPlayMode(mAutoPlay);

}
void GameView::OnAutoPlayMode(wxCommandEvent& event)
{
    mAutoPlay = !mAutoPlay;
    mGame.UpdateAutoPlayMode(mAutoPlay);
}
void GameView::DisplayStar(std::shared_ptr<wxGraphicsContext> gc)
{
    double ratio = mGame.GetGameStateManager()->GetScore()/(FullPoint*mGame.GetTotalNote());
    if (ratio >= 0.8){
        auto starBitmap = make_unique<wxBitmap>(threestars, wxBITMAP_TYPE_ANY);
        // Calculate positions to center the text
        double xPos = (mGame.GetWidth() - starBitmap->GetWidth()) / 2;
        double yPos = (mGame.GetHeight() - starBitmap->GetHeight()) / 2;

        gc->DrawBitmap(*starBitmap,
                     xPos,
                     yPos,
                     starBitmap->GetWidth(),
                     starBitmap->GetHeight());
    }
//    else if (ratio >= 0.5 && ratio < 0.8){
//        auto starBitmap = make_unique<wxBitmap>(twostars, wxBITMAP_TYPE_ANY);
//        // Calculate positions to center the text
//        double xPos = (mGame.GetWidth() - starBitmap->GetWidth()) / 2;
//        double yPos = (mGame.GetHeight() - starBitmap->GetHeight()) / 2;
//
//        gc->DrawBitmap(*starBitmap,
//                       xPos,
//                       yPos,
//                       starBitmap->GetWidth(),
//                       starBitmap->GetHeight());
//    } else
//    {
//        auto starBitmap = make_unique<wxBitmap>(onestar, wxBITMAP_TYPE_ANY);
//        // Calculate positions to center the text
//        double xPos = (mGame.GetWidth() - starBitmap->GetWidth()) / 2;
//        double yPos = (mGame.GetHeight() - starBitmap->GetHeight()) / 2;
//
//        gc->DrawBitmap(*starBitmap,
//                       xPos,
//                       yPos,
//                       starBitmap->GetWidth(),
//                       starBitmap->GetHeight());
//    }
}

