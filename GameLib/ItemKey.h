/**
 * @file ItemKey.h
 * @author Naod Ghebredngl
 *
 * File for Item Key Class
 */

#ifndef PROJECT1_TRACK_H
#define PROJECT1_TRACK_H

#include "Game.h"
#include "Item.h"
#include <string>
#include <vector>

// Forward reference
class ItemSoundboard;


/**
 * Class for Item Key
 */
class ItemKey {
private:

    // The soundboard this track is contained in
    ItemSoundboard  *mItemSoundBoard;

    /// The track number
    int mTrack = 0;

    /// The bitmap we can display for this soundboard
    std::unique_ptr<wxBitmap> mKeyBitmap;

    wxString  mKey = "";  ///< ItemTrackLine of the track
    double mWidth = 0;  ///< Width of the key
    double mHeight = 0; ///< Length of the key
    // Item location in the game
    double  mX2 = 0;     ///< X location for the center of the item
    double  mY2 = 0;     ///< Y location for the center of the item
    double  mX1 = 0;     ///< X location for another point of the item
    double  mY1 = 0;     ///< Y location for another point of the item

public:
    /// Default constructor (disabled)
    ItemKey() = delete;

    /// Copy constructor (disabled)
    ItemKey(const ItemKey &) = delete;

    /// Assignment operator
    void operator=(const ItemKey &) = delete;

    ItemKey(ItemSoundboard *soundboard);

    /**
     * @return key item
     */
    wxString GetKey() { return mKey; }


    /**
     * The X1 location of the item
     * @return X1 location in pixels
     */
    double GetX1() const { return mX1; }

    /**
     * The Y1 location of the item
     * @return Y1 location in pixels
     */
    double GetY1() const { return mY1; }

    /**
     * The X2 location of the item
     * @return X2 location in pixels
     */
    double GetX2() const { return mX2; }

    /**
     * The Y2 location of the item
     * @return Y2 location in pixels
     */
    double GetY2() const { return mY2; }

    void XmlLoad(wxXmlNode *node);

    void Draw(std::shared_ptr<wxGraphicsContext> gp);

    /**
     * The Id of the item
     * @return Id
     */
    int GetTrack() const {return mTrack;}

    void SetLocation(double x1, double x2, double y1,double y2);

};


#endif //PROJECT1_TRACK_H
