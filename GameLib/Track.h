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
 * Class for Track that derives from Item
 */
class Track : public Item {
private:

    /// Member variable for amount of tilt needed
    int mTilt = -130;

    /// Member variable for track number
    int mTrack = 0;

public:
    /// Default constructor (disabled)
    Track() = delete;

    /// Copy constructor (disabled)
    Track(const Track &) = delete;

    /// Assignment operator
    void operator=(const Track &) = delete;

    Track(Game *game, const std::wstring &filename);

};


#endif //PROJECT1_TRACK_H
