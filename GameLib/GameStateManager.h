/**
 * @file GameStateManager.h
 * @author Angelina Jolie Daoud
 *
 * File for Game State Manager Class
 */

#ifndef PROJECT1_GAMELIB_GAMESTATEMANAGER_H
#define PROJECT1_GAMELIB_GAMESTATEMANAGER_H

#include <utility>

// Forward reference
class Game;

/**
 * Base class for Game State Manager
 */
class GameStateManager
{
private:
    Game* mGame; ///< Game instance
    int mScore=0; ///< Current score
    int mCurrentMeasure = 0 ; ///< Current Measure
    int mCurrentBeat = 0; ///< Current Beat

public:
    GameStateManager(Game* game);

    ~GameStateManager();

    void UpdateScore(int points);
    void SetDurationBonus(float duration);

    int GetScore();
    std::pair<int, int> GetCurrentMeasureAndBeat() const;

    void UpdateScoreboard(bool soundPlayed, float durationHeld, float totalDuration);
    void UpdateMeasureAndBeat();
};

#endif //PROJECT1_GAMELIB_GAMESTATEMANAGER_H
