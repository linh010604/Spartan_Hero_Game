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

class GameStateManager
{
private:
    Game* mGame;
    int mScore;
    int mCurrentMeasure;
    int mCurrentBeat;

public:
    GameStateManager(Game* game);

    void UpdateScore(int points);
    void UpdateMeasureAndBeat(int measure, int beat);
    void SetDurationBonus(float duration);

    int GetScore() const;
    std::pair<int, int> GetCurrentMeasureAndBeat() const;

    void UpdateScoreboard(bool soundPlayed, float durationHeld, float totalDuration);
};

#endif //PROJECT1_GAMELIB_GAMESTATEMANAGER_H
