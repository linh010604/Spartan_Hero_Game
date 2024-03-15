/**
 * @file ItemMeter.cpp
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "ItemMeter.h"

/**
 * Constructor
 * @param game The game this item is a member of
 */
ItemMeter::ItemMeter(Game *game) : Item(game)
{
}

/**
 *
 * @param value
 */
void ItemMeter::UpdateMeter(double value)
{
    mCurrentMeterValue = value;

}