/**
 * @file ItemTrackLine.h
 * @author Nicolas Roberts
 *
 * File for trackline class
 */

#ifndef PROJECT1_TRACKLINE_H
#define PROJECT1_TRACKLINE_H

#include "Game.h"
#include "Item.h"
#include <string>
#include <vector>

/**
 * Allows access to ItemSoundBoars without creating a circular dependency.
 */
class ItemSoundBoard;


/**
 * Class for ItemTrackLine that derives from Item
 */
class ItemTrackLine {
private:

    // The soundboard this track is contained in
    ItemSoundBoard  *mItemSoundBoard;

    /// The track number
    int mTrack = 0;

    // Item location in the game
    double  mX1 = 0;     ///< X1 location for the center of the item
    double  mY1 = 0;     ///< Y1 location for the center of the item
    double  mX2 = 0;     ///< X2 location for the center of the item
    double  mY2 = 0;     ///< Y2 location for the center of the item

public:
    /// Default constructor (disabled)
    ItemTrackLine() = delete;

    /// Copy constructor (disabled)
    ItemTrackLine(const ItemTrackLine &) = delete;

    /// Assignment operator
    void operator=(const ItemTrackLine &) = delete;

    ItemTrackLine(ItemSoundBoard *soundboard, double x1, double y1, double x2, double y2);

    void Draw(std::shared_ptr<wxGraphicsContext> gp);

};

#endif //PROJECT1_KEY_H
