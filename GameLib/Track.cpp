/**
 * @file Track.cpp
 * @author Naod Ghebredngl
 */

#include "pch.h"
#include "Track.h"
#include "Item.h"
#include "Game.h"

/**
 * Constructor
 * @param game The game this item is a member of
 * @param filename Image file name for the item
 */
Track::Track(Game *game, const std::wstring &filename) : Item(game)
{

}
