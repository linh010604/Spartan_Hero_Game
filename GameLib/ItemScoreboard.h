/**
 * @file ItemScoreboard.h
 * @author Angelina Jolie Daoud
 *
 * File for ItemScoreboard class
 */

#ifndef PROJECT1_GAMELIB_ITEMSCOREBOARD_H
#define PROJECT1_GAMELIB_ITEMSCOREBOARD_H

#include "Item.h"
#include "DeclarationScoreBoard.h"

/**
 * Class for a Scoreboard Item
 */

class ItemScoreboard : public Item
{
public:
    /// Default constructor (disabled)
    ItemScoreboard() = delete;

    /// Copy constructor (disabled)
    ItemScoreboard(const ItemScoreboard &) = delete;

    /// Assignment operator
    void operator=(const ItemScoreboard &) = delete;

    ItemScoreboard(Game *game);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitItemScoreboard(this); }



private:


};

#endif //PROJECT1_GAMELIB_ITEMSCOREBOARD_H

