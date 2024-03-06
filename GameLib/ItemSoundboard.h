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
 * Allows access to Track without creating a circular dependency.
 */
class Track;

/**
 * Class for a Soundboard Item
 */
class ItemSoundBoard : public Item
{
private:
    /// All of the tracks to populate our soundboard
    std::vector<std::shared_ptr<Track>> mTracks;
public:
    /// Default constructor (disabled)
    ItemSoundBoard() = delete;

    /// Copy constructor (disabled)
    ItemSoundBoard(const ItemSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundBoard &) = delete;

    ItemSoundBoard(Game *game);

    void AddTrack(std::shared_ptr<Track> track);

    /**
    * Load the attributes for Soundboard node.
    * @param node The Xml node we are loading the declaration from
    */
    void XmlLoad(wxXmlNode *node) override;

    /**
     * Draw this item
     * @param gp Device context to draw on
     * @param soundboard The corresponding declaration
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> soundboard) override;

};

#endif //PROJECT1_SOUNDBOARD_H
