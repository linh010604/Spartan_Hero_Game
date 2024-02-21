//
// Created by naodg on 2/21/2024.
//

#include "pch.h"
#include "Puck.h"
#include "Game.h"


/**
 * Constructor
 * @param game The game this item is a member of
 * @param filename Image file name for the item
 */
Puck::Puck(Game *game, const std::wstring &filename) : Item(game, filename)
{
    // Initialize base variables
    speed = 0;

}

// void Puck::Update(elapsed) {}