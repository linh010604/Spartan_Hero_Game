/**
 * @file Track.h
 * @author Naod Ghebredngl
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
public:

    Track(Game *game, const std::wstring &filename);

};


#endif //PROJECT1_TRACK_H
