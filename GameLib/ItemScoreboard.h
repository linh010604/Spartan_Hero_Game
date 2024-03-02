/**
 * @file ItemScoreboard.h
 * @author Angelina Jolie Daoud
 *
 * File for ItemScoreboard class
 */

#ifndef PROJECT1_GAMELIB_ITEMSCOREBOARD_H
#define PROJECT1_GAMELIB_ITEMSCOREBOARD_H

#include "Item.h"

class ItemScoreBoard : public Item
{
public:
    /// Default constructor (disabled)
    ItemScoreBoard() = delete;

    /// Copy constructor (disabled)
    ItemScoreBoard(const ItemScoreBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemScoreBoard &) = delete;

    ItemScoreBoard(Game *game);

};

#endif //PROJECT1_GAMELIB_ITEMSCOREBOARD_H

