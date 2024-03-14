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
    int mScore=0;
    int mCurrentMeasure = 0 ;
    int mCurrentBeat = 0;

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
