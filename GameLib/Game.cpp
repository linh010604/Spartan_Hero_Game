/**
 * @file Game.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include "Declaration.h"
#include "DeclarationImage.h"
#include "DeclarationMeter.h"
#include "DeclarationSoundBoard.h"
#include "DeclarationScoreBoard.h"
#include "DeclarationNote.h"
#include "ItemImage.h"
#include "ItemMeter.h"
#include "ItemSoundboard.h"
#include "ItemScoreboard.h"
#include "Music.h"
#include "Sound.h"
#include "ItemVisitor.h"
#include "ItemSoundBoardVisitor.h"
#include "DeclarationVisitor.h"
#include "DeclarationNoteVisitor.h"
#include <memory>
#include <thread>
#include <chrono>

using namespace std;

bool const BeforeTrack = true;
bool const AfterTrack = false;
///Seconds in a minute
double const SecondsPerMinute = 60;

double const StartingBeat = 4;

Game::Game(ma_engine *PEngine) : mAudioEngine(PEngine){
    mGameStateManager = std::make_shared<GameStateManager>(this);
}

std::shared_ptr<GameStateManager> Game::GetGameStateManager() {
    return mGameStateManager;
}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height) {
    // Width of virtual pixels
    int virtualWidth = mVirtualWidth;
    // Height of virtual pixels
    int virtualHeight = mVirtualHeight;

    // Creates Scale for X values
    auto scaleX = double(width) / double(virtualWidth);
    // Creates Scale for Y values
    auto scaleY = double(height) / double(virtualHeight);
    // Gets minimum of Scales for X and Y
    mScale = std::min(scaleX, scaleY);

    // Creates offset for X
    mXOffset = (width - virtualWidth * mScale) / 2.0;
    // Creates offset for Y
    mYOffset = (height - virtualHeight * mScale) > 0 ? (height - virtualHeight * mScale) / 2.0 : 0;

    wxImage puckImage(L"images/puck-a.png", wxBITMAP_TYPE_ANY); // Adjust path as necessary
    if (puckImage.IsOk()) {
        wxBitmap puckBitmap(puckImage);
        double puckX = 3000; // Example X position
        double puckY = 3000; // Example Y position
        graphics->DrawBitmap(puckBitmap, puckX, puckY, puckBitmap.GetWidth(), puckBitmap.GetHeight());
    }

    // Saves current state of graphics
    graphics->PushState();
    // Translates the coordinates system using offsets
    graphics->Translate(mXOffset, mYOffset);
    // Scales coordinate system
    graphics->Scale(mScale, mScale);

    for (auto item : mItems)
    {
        for (auto declaration : mDeclarations)
        {
            if (item->GetId() == declaration->GetId()){
                declaration->Draw(graphics,item->GetX(), item->GetY(),BeforeTrack);
                item->Draw(graphics, declaration,BeforeTrack);
                declaration->Draw(graphics,item->GetX(), item->GetY(),AfterTrack);
                item->Draw(graphics, declaration,AfterTrack);
                break;
            }
        }

    }


}

/**  Handle updates for animation
* @param elapsed The time since the last update
*/
void Game::Update(double elapsed)
{
    mTimePLaying += elapsed;
    if (mTimePLaying >= 2.0) mAbsoluteBeat += elapsed * mBeatsPerMinute/ SecondsPerMinute;
    double beatsPerSecond = mBeatsPerMinute/SecondsPerMinute;
    mTimeOnTrack = mBeatsPerMeasure/beatsPerSecond;

    GameUpdate();

    for (auto music:mMusic){
        music->Update(elapsed, mTimeOnTrack);
    }
    mGameStateManager->UpdateMeasureAndBeat();
}

/**
 * Handle a key press event
 * @param key The key was pressed
 */
void Game::PressKey(wxChar key, double elapsed)
{

}

void Game::DrawNote(std::shared_ptr<wxGraphicsContext> gc)
{
    for (auto music : mMusic)
    {
        music->Draw(gc);
    }
}
void Game::GameUpdate()
{
    if (mState != GameState::Closing && wxRound(mAbsoluteBeat) >= (mMeasure+1) * 4){
        mState = GameState::Closing;
        mTimePLaying = 0;
        mAudio[0]->PlayEnd();
    }
    else if (wxRound(4-mAbsoluteBeat) < 0 && mState != GameState::Playing)
    {
        mState = GameState::Playing;
    }
    else if (mTimePLaying > 2.0 && mState == GameState::Ready)
    {
        mState = GameState::Countdown;
    }
    else if (mState == GameState::Countdown && mAbsoluteBeat >= StartingBeat && !mBackPlaying)
    {
        mAudio[0]->LoadSound(mAudioEngine);
        mAudio[0]->PlaySound();
        mBackPlaying =! mBackPlaying;
    }


}

void Game::UpdateAutoPlayMode()
{
    mAutoPlay = !mAutoPlay;
}

