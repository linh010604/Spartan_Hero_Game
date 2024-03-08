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
 * Allows access to ItemKey without creating circular dependency.
 */
class ItemKey;

/**
 * Allows access to ItemTrackLine without creating circular dependency.
 */
class ItemTrackLine;

/**
 * Class for a Soundboard Item
 */
class ItemSoundBoard : public Item
{
private:

    /// All of the keys to populate our soundboard
    std::vector<std::shared_ptr<ItemKey>> mKeys;

    /// All of the tracks to populate our soundboard
    std::vector<std::shared_ptr<ItemTrackLine>> mTracks;

public:
    /// Default constructor (disabled)
    ItemSoundBoard() = delete;

    /// Copy constructor (disabled)
    ItemSoundBoard(const ItemSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundBoard &) = delete;

    ItemSoundBoard(Game *game);

    void AddTrack(std::shared_ptr<ItemKey> track);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> soundboard) override;

};

#endif //PROJECT1_SOUNDBOARD_H
