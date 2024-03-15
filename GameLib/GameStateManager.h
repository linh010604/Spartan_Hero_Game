/**
 * @file GameStateManager.h
 * @author Angelina Jolie Daoud
 *
 *
 */

#ifndef PROJECT1_GAMELIB_GAMESTATEMANAGER_H
#define PROJECT1_GAMELIB_GAMESTATEMANAGER_H

#include <utility>

class Game;

/**
 * Class to manage score of the game
 */
class GameStateManager
{
private:

    /// The game this class mange score
    Game *mGame;

    /// Current score of the game
    int mScore = 0;

    /// Current measure og the game
    int mCurrentMeasure = 0;

    /// Current beat of the game
    int mCurrentBeat = 0;

public:
    GameStateManager(Game *game);

    ~GameStateManager();

    void UpdateScore(int points);
    void SetDurationBonus(float duration);

    int GetScore();
    std::pair<int, int> GetCurrentMeasureAndBeat() const;

    void UpdateMeasureAndBeat();
};

#endif //PROJECT1_GAMELIB_GAMESTATEMANAGER_H
