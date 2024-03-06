/**
 * @file Track.h
 * @author Naod Ghebredngl
 *
 * File for Track class
 */

#ifndef PROJECT1_TRACK_H
#define PROJECT1_TRACK_H

#include "Game.h"
#include "Item.h"
#include <string>
#include <vector>

/**
 * Allows access to ItemSoundBoars without creating a circular dependency.
 */
class ItemSoundBoard;

/**
 * Class for Track that derives from Item
 */
class Track {
private:

    /// The soundboard this track is contained in
    ItemSoundBoard  *mItemSoundBoard;

    /// The track number
    int mTrack = 0;

    /// The bitmap we can display for this soundboard
    std::unique_ptr<wxBitmap> mKeyBitmap;

    wxString  mKey = "";  ///< Key of the track
    double mWidth = 0;  ///< Width of the key
    double mHeight = 0; ///< Length of the key
    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

public:
    /// Default constructor (disabled)
    Track() = delete;

    /// Copy constructor (disabled)
    Track(const Track &) = delete;

    /// Assignment operator
    void operator=(const Track &) = delete;

    Track(ItemSoundBoard *soundboard);

    /**
     * Set X location of the item
     * @param x X position
     */
    void SetX(double x) { mX = x; }

    /**
     * Set Y location of the item
     * @param y Y position
     */
    void SetY(double y) { mY = y; }

    void XmlLoad(wxXmlNode *node);

    /**
     * Draw this item
     * @param gp Device context to draw on
     * @param x X position
     * @param y Y position
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y);

};


#endif //PROJECT1_TRACK_H
