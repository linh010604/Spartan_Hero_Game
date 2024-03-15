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

GameStateManager::GameStateManager(Game* game)
    : mGame(game), mScore(0), mCurrentMeasure(0), mCurrentBeat(0)
    {
    }

void GameStateManager::UpdateScore(int points)
{
    mScore += points;
}

void GameStateManager::UpdateMeasureAndBeat()
{
    mCurrentMeasure = wxRound(mGame->GetAbsoluteBeat())/mGame->GetBeatsPerMersure();
    mCurrentBeat = wxRound(mGame->GetAbsoluteBeat()) - mCurrentMeasure * mGame->GetBeatsPerMersure()+1;
}

void GameStateManager::SetDurationBonus(float duration)
{
    int bonus = static_cast<int>(MaxDurationBonus * duration);
    mScore += bonus;
}

int GameStateManager::GetScore()
{
    return mScore;
}

std::pair<int, int> GameStateManager::GetCurrentMeasureAndBeat() const
{
    return {mCurrentMeasure, mCurrentBeat};
}

GameStateManager::~GameStateManager()
{

}



