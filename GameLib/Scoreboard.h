/**
 * @file Scoreboard.h
 * @author Angelina Jolie Daoud
 *
 *
 */

#ifndef PROJECT1_GAMELIB_SCOREBOARD_H
#define PROJECT1_GAMELIB_SCOREBOARD_H

#include "pch.h"
#include "Game.h"
#include "Item.h"

/**
 * Class for Scoreboard that derives from Item
 */

class Scoreboard : public Item{
private:

public:
    Scoreboard(Game *game, const std::wstring &filename);


};

#endif //PROJECT1_GAMELIB_SCOREBOARD_H
