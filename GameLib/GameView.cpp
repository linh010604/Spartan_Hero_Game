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


/// Frame duration in milliseconds
const int FrameDuration = 30;

/**
* The event table that connects window events
*/
wxBEGIN_EVENT_TABLE(GameView, wxWindow)
        EVT_PAINT(GameView::OnPaint)
        EVT_LEFT_DOWN(GameView::OnLeftDown)
wxEND_EVENT_TABLE()

GameView::GameView(ma_engine *audioEngine) : mGame(audioEngine)
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

    Bind(wxEVT_KEY_DOWN, &GameView::OnKeyDown, this);
    mainFrame->Bind(wxEVT_KEY_UP, &GameView::OnKeyUp, this);
    // Binds left down function with event
    Bind(wxEVT_LEFT_DOWN, &GameView::OnLeftDown, this);


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
    mTime = newTime;
    // Create a graphics context
    auto gc = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create(dc));

    // Tell the game class to draw
    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

}

void GameView::OnLeftDown(wxMouseEvent &event)
{
    // On left down mouse click gets X and Y values
    mGame.OnLeftDown(event.GetX(), event.GetY());
}

/**
 * Handle level choosing event
 * @param event Command event
 */
void GameView::OnLevelOption(wxCommandEvent& event)
{
    wxString filename;

    switch(event.GetId())
    {
        case IDM_LEVEL0:
            filename = L"levels/level0.xml";
            mGame.Load(filename);
            Refresh();
            break;
        case IDM_LEVEL1:
            filename = L"levels/level1.xml";
            mGame.Load(filename);
            Refresh();
            break;
        case IDM_LEVEL2:
            filename = L"levels/level2.xml";
            mGame.Load(filename);
            Refresh();
            break;
        case IDM_LEVEL3:
            filename = L"levels/level3.xml";
            mGame.Load(filename);
            Refresh();
            break;

    }

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
    Sound sound;

    switch(key)
    {
        case(wxChar(65)):
            sound.SetAudioFile(L"trumpet/C4.wav");
            break;
        case(wxChar(83)):
            sound.SetAudioFile(L"trumpet/Db4.wav");
            break;
        case(wxChar(68)):
            sound.SetAudioFile(L"trumpet/Eb4.wav");
            break;
        case(wxChar(70)):
            sound.SetAudioFile(L"trumpet/E4.wav");
            break;

        case(wxChar(74)):
            sound.SetAudioFile(L"trumpet/C5.wav");
            break;
        case(wxChar(75)):
            sound.SetAudioFile(L"trumpet/Db5.wav");
            break;
        case(wxChar(76)):
            sound.SetAudioFile(L"trumpet/Eb5.wav");
            break;
        case(wxChar(59)):
            sound.SetAudioFile(L"trumpet/E5.wav");
            break;

        default:
            sound.SetAudioFile(L"trumpet/B4.wav");
            std::cout << "Not a key" << std::endl;
            break;
    }
    sound.SetVolume(0.5);
    sound.LoadSound(mGame.GetAudioEngine());

    sound.PlaySound();
    std::this_thread::sleep_for(std::chrono::seconds(2)); //pauses for 2 seconds
    sound.PlayEnd();
}

/**
 * Handle a key release event
 * @param event Key release event
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