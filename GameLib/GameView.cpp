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

/// Full points awarded for a correct action.
const int FullPoint = 10;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Filename for 3 stars image
const wstring threestars = L"stars/threestar.png";

/// Filename for 2 stars image
const wstring twostars = L"stars/twostar.png";

/// Filename for 1 star image
const wstring onestar = L"stars/onestar.png";

/**
 * Constructor
 * @param audioEngine The audio engine for miniaudio
 */
GameView::GameView(ma_engine *audioEngine) : mGame(audioEngine), mAudioEngine(audioEngine)
{
}

/**
 * Initialize the game view class.
 * @param mainFrame The parent window for this class
 */
void GameView::Initialize(wxFrame *mainFrame)
{
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

    mGame.Load(wxString::Format("levels/level%d.xml", mCurrentLevel));
    Refresh();

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);

    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);

    Bind(wxEVT_TIMER, &GameView::OnTimer, this);

    mStopWatch.Start();

}

/**
 * Handles the paint event for the game view.
 *
 * This function is responsible for drawing the game scene, including graphics, text, and notices.
 *
 * @param event The paint event.
 */
void GameView::OnPaint(wxPaintEvent &event)
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

    if(mDisplayLevelNotice && mLevelNoticeStopWatch.Time() < LevelNoticeDuration * 1000)
    {
        if(mCurrentLevel != 3)
        {

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
        }

        else
        {
            wxString noticeText = wxString::Format("     Welcome \n to the Carnival!");
            int smallerFontSize = NoticeSize - 20;
            wxFont font(smallerFontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
            gc->SetFont(font, LevelNoticeColor);

            // Measure text size
            double textWidth, textHeight;
            gc->GetTextExtent(noticeText, &textWidth, &textHeight, nullptr, nullptr);

            // Calculate positions to center the text
            double xPos = (mGame.GetWidth() - textWidth) / 2;
            double yPos = (mGame.GetHeight() - textHeight) / 2;

            gc->DrawText(noticeText, xPos, yPos);

        }

    }
    else if(mDisplayLevelNotice)
    {
        mDisplayLevelNotice = false;
    }

    if(mGame.GetState() == Game::GameState::Closing)
    {
        if(mClosingTime == 0)
        {
            mClosingTime = mStopWatch.Time();
        }
        if(mStopWatch.Time() - mClosingTime <= LevelNoticeDuration * 1000)
        {
            if(mCurrentLevel != 3)
            {

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

            else
            {
                wxString noticeText = wxString::Format("Hope You Had Fun!");
                wxFont font(NoticeSize - 5, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
                gc->SetFont(font, LevelNoticeColor);

                // Measure text size
                double textWidth, textHeight;
                gc->GetTextExtent(noticeText, &textWidth, &textHeight, nullptr, nullptr);

                // Calculate positions to center the text
                double xPos = (mGame.GetWidth() - textWidth) / 2;
                double yPos = (mGame.GetHeight() - textHeight) / 2;

                gc->DrawText(noticeText, xPos, yPos);

            }

        }
        else if(mStopWatch.Time() - mClosingTime >= 2 * LevelNoticeDuration * 1000)
        {
            mCurrentLevel = (mCurrentLevel + 1) % 4;
            Sequence();
        }
        else if(mStopWatch.Time() - mClosingTime < 2 * LevelNoticeDuration * 1000
            && mStopWatch.Time() - mClosingTime > LevelNoticeDuration * 1000)
        {

            DisplayStar(gc);
        }

    }

    // Restores state of graphics
    gc->PopState();

    mGame.Update(elapsed);

}

/**
 * CHeck if we should display welcome notice for each level
 * @param level current level
 */
void GameView::DisplayLevelNotice(int level)
{
    mCurrentLevel = level;
    mDisplayLevelNotice = true;
    mLevelNoticeStopWatch.Start();
}

/**
 * Handle level choosing event
 * @param event Command event
 */
void GameView::OnLevelOption(wxCommandEvent &event)
{
    wxString filename;
    int levelNumber = 0;

    switch(event.GetId())
    {
        case IDM_LEVEL0:filename = L"levels/level0.xml";
            levelNumber = 0;
            break;
        case IDM_LEVEL1:filename = L"levels/level1.xml";
            levelNumber = 1;
            break;
        case IDM_LEVEL2:filename = L"levels/level2.xml";
            levelNumber = 2;
            break;
        case IDM_LEVEL3:filename = L"levels/level3.xml";
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
void GameView::OnKeyDown(wxKeyEvent &event)
{
    wxChar key = event.GetKeyCode();
    mGame.PressKey(key);

}

/**
 * Handle a key release event
 * @param event ItemTrackLine release event
 */
void GameView::OnKeyUp(wxKeyEvent &event)
{
    wxChar key = event.GetKeyCode();
    mGame.KeyUp(key);
}

/**
 * Handle timer events
 * @param event timer event
 */
void GameView::OnTimer(wxTimerEvent &event)
{
    Refresh();
}

/**
 * Handle sequencing when each level complete
 */
void GameView::Sequence()
{
    mGame = Game(mAudioEngine);
    mGame.Load(wxString::Format("levels/level%d.xml", mCurrentLevel));
    mGame.UpdateAutoPlayMode(mAutoPlay);
    Refresh();
    mTime = 0;
    mDisplayLevelNotice = true;
    mClosingTime = 0;
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    mStopWatch.Start();
    DisplayLevelNotice(mCurrentLevel);

}

/**
 * Handle the autoplay mode
 * @param event Command event
 */
void GameView::OnAutoPlayMode(wxCommandEvent &event)
{
    mAutoPlay = !mAutoPlay;
    mGame.UpdateAutoPlayMode(mAutoPlay);
}

/**
 * Draw the star at the end of level to show playing progress
 * @param gc A shared pointer to a wxGraphicsContext object used for drawing.
 */
void GameView::DisplayStar(std::shared_ptr<wxGraphicsContext> gc)
{
    double realScore = mGame.GetGameStateManager()->GetScore();
    double totalScore = (FullPoint * mGame.GetTotalNote());
    double ratio = realScore / totalScore;
    if(ratio >= 0.8)
    {
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
    else if(ratio >= 0.5 && ratio < 0.8)
    {
        auto starBitmap = make_unique<wxBitmap>(twostars, wxBITMAP_TYPE_ANY);
        // Calculate positions to center the text
        double xPos = (mGame.GetWidth() - starBitmap->GetWidth()) / 2;
        double yPos = (mGame.GetHeight() - starBitmap->GetHeight()) / 2;

        gc->DrawBitmap(*starBitmap,
                       xPos,
                       yPos,
                       starBitmap->GetWidth(),
                       starBitmap->GetHeight());
    }
    else
    {
        auto starBitmap = make_unique<wxBitmap>(onestar, wxBITMAP_TYPE_ANY);
        // Calculate positions to center the text
        double xPos = (mGame.GetWidth() - starBitmap->GetWidth()) / 2;
        double yPos = (mGame.GetHeight() - starBitmap->GetHeight()) / 2;

        gc->DrawBitmap(*starBitmap,
                       xPos,
                       yPos,
                       starBitmap->GetWidth(),
                       starBitmap->GetHeight());
    }
}
