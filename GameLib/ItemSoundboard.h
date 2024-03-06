/**
 * @file ItemSoundboard.h
 * @author Nicolas Roberts
 * @author Linh Nguyen
 *
 * File for ItemSoundboard class
 */

#ifndef PROJECT1_SOUNDBOARD_H
#define PROJECT1_SOUNDBOARD_H

#include "Item.h"

/**
 * Class for a Soundboard Item
 */
class ItemSoundBoard : public Item
{
public:
    /// Default constructor (disabled)
    ItemSoundBoard() = delete;

    /// Copy constructor (disabled)
    ItemSoundBoard(const ItemSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundBoard &) = delete;

    ItemSoundBoard(Game *game);
};

#endif //PROJECT1_SOUNDBOARD_H
