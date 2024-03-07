/**
 * @file ItemMeter.h
 * @author Nicolas Roberts
 *
 * File for ItemMeter class
 */

#ifndef PROJECT1_GAMELIB_ITEMMETER_H
#define PROJECT1_GAMELIB_ITEMMETER_H

#include "Item.h"

/**
 * Class for a Meter Item
 */
class ItemMeter : public Item
{
public:
    /// Default constructor (disabled)
    ItemMeter() = delete;

    /// Copy constructor (disabled)
    ItemMeter(const ItemMeter &) = delete;

    /// Assignment operator
    void operator=(const ItemMeter &) = delete;

    ItemMeter(Game *game);

};

#endif //PROJECT1_GAMELIB_ITEMMETER_H
