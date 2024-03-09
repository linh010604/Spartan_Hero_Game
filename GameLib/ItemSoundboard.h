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
class ItemSoundboard : public Item
{
private:

    /// All of the keys to populate our soundboard
    std::vector<std::shared_ptr<ItemKey>> mKeys;

    /// All of the tracks to populate our soundboard
    std::vector<std::shared_ptr<ItemTrackLine>> mTracks;

public:
    /// Default constructor (disabled)
    ItemSoundboard() = delete;

    /// Copy constructor (disabled)
    ItemSoundboard(const ItemSoundboard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundboard &) = delete;

    ItemSoundboard(Game *game);

    void AddTrack(std::shared_ptr<ItemKey> track);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> soundboard) override;

    void DrawRedLines(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> soundboard, double puckX, double puckY);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitItemSoundboard(this); }
};

#endif //PROJECT1_SOUNDBOARD_H
