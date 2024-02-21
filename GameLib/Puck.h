//
// Created by naodg on 2/21/2024.
//

/**
 * @file Puck.h
 * @author Naod Ghebredngl
 */

#ifndef PROJECT1_PUCK_H
#define PROJECT1_PUCK_H


#include "Game.h"
#include "Item.h"

/**
 * Class for Puck that derives from Item
 */
class Puck : public Item {

private:
    // variables for puck go here
    // lots more to add
    double speed;
public:
    Puck(Game *game, const std::wstring &filename);

    // Update function most likely needed




};


#endif //PROJECT1_PUCK_H
