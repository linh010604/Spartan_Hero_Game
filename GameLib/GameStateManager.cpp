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

/// Score we get when we successfully hit a note
const int GoodSoundScore = 10;

/**
 * Constructor The game this declaration is a member of
 * @param game
 */
GameStateManager::GameStateManager(Game *game)
    : mGame(game), mScore(0), mCurrentMeasure(0), mCurrentBeat(0)
{
}

/**
 * Updates the score by adding the given points.
 *
 * @param points The points to be added to the score.
 */
void GameStateManager::UpdateScore(int points)
{
    mScore += points;
}

/**
 * Updates the current measure and beat based on the game's absolute beat.
 */
void GameStateManager::UpdateMeasureAndBeat()
{
    mCurrentMeasure = wxRound(mGame->GetAbsoluteBeat()) / mGame->GetBeatsPerMersure();
    mCurrentBeat = wxRound(mGame->GetAbsoluteBeat()) - mCurrentMeasure * mGame->GetBeatsPerMersure() + 1;
}

/**
 * Sets the duration bonus for the current gameplay.
 *
 * @param duration The duration of the action to calculate bonus.
 */
void GameStateManager::SetDurationBonus(float duration)
{
    int bonus = static_cast<int>(MaxDurationBonus * duration);
    mScore += bonus;
}

/**
 * Retrieves the current score.
 *
 * @return The current score.
 */
int GameStateManager::GetScore()
{
    return mScore;
}

/**
 * Retrieves the current measure and beat as a pair.
 *
 * @return A pair representing the current measure and beat.
 */
std::pair<int, int> GameStateManager::GetCurrentMeasureAndBeat() const
{
    return {mCurrentMeasure, mCurrentBeat};
}

/**
 * Updates the scoreboard based on the sound played, duration held, and total duration.
 *
 * @param soundPlayed Indicates whether a sound was played.
 * @param durationHeld The duration for which the sound was held.
 * @param totalDuration The total duration of the action.
 */
void GameStateManager::UpdateScoreboard(bool soundPlayed, float durationHeld, float totalDuration)
{
    if(soundPlayed)
    {
        UpdateScore(GoodSoundScore);

        if(totalDuration > 0)
        {
            float durationPercentage = durationHeld / totalDuration;
            int bonus = static_cast<int>(MaxDurationBonus * durationPercentage);
            bonus = (bonus > MaxDurationBonus) ? MaxDurationBonus : bonus;
            UpdateScore(bonus);
        }
    }
}

/**
 * Destructor
 */
GameStateManager::~GameStateManager()
{

}
