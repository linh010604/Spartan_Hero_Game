/**
 * @file GameStateManager.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "GameStateManager.h"
#include "Game.h"

/// The maximum bonus we can get for
/// holding for the duration for a long sound
const int MaxDurationBonus = 10;

/**
 * Constructor
 * @param game The game this item is a member of
 */
GameStateManager::GameStateManager(Game* game)
    : mGame(game), mScore(0), mCurrentMeasure(0), mCurrentBeat(0)
    {
    }

/**
 * Update the score of the game
 * @param points total point to add
 */
void GameStateManager::UpdateScore(int points)
{
    mScore += points;
}

/**
 * Update current beats and measure for game
 */
void GameStateManager::UpdateMeasureAndBeat()
{
    mCurrentMeasure = wxRound(mGame->GetAbsoluteBeat())/mGame->GetBeatsPerMersure();
    mCurrentBeat = wxRound(mGame->GetAbsoluteBeat()) - mCurrentMeasure * mGame->GetBeatsPerMersure()+1;
}

/**
 * Update the score according to bonus point for long note
 * @param duration the duration of the note
 */
void GameStateManager::SetDurationBonus(float duration)
{
    int bonus = static_cast<int>(MaxDurationBonus * duration);
    mScore += bonus;
}

/**
 * Get current score of the game
 * @return mScore
 */
int GameStateManager::GetScore()
{
    return mScore;
}

/**
 * Get current measure and beats of the game
 * @return mCurrentMeasure and m CurrentBeat
 */
std::pair<int, int> GameStateManager::GetCurrentMeasureAndBeat() const
{
    return {mCurrentMeasure, mCurrentBeat};
}

GameStateManager::~GameStateManager()
{

}



