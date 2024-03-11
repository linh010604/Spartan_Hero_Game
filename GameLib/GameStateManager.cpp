/**
 * @file GameStateManager.cpp
 * @author Angelina Jolie Daoud
 */

#include "GameStateManager.h"
#include "Game.h"

/// The maximum bonus we can get for
/// holding for the duration for a long sound
const int MaxDurationBonus = 10;

/// Score we get when we successfully hit a note
const int GoodSoundScore = 10;

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

void GameStateManager::UpdateScoreboard(bool soundPlayed, float durationHeld, float totalDuration)
{
    if (soundPlayed)
    {
        UpdateScore(GoodSoundScore);

        if (totalDuration > 0)
        {
            float durationPercentage = durationHeld / totalDuration;
            int bonus = static_cast<int>(MaxDurationBonus * durationPercentage);
            bonus = (bonus > MaxDurationBonus) ? MaxDurationBonus : bonus;
            UpdateScore(bonus);
        }
    }
}
GameStateManager::~GameStateManager()
{

}



