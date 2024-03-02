/**
 * @file ItemImage.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_ITEMIMAGE_H
#define PROJECT1_GAMELIB_ITEMIMAGE_H

#include "Item.h"

class ItemImage : public Item {
public:
    /// Default constructor (disabled)
    ItemImage() = delete;

    /// Copy constructor (disabled)
    ItemImage(const ItemImage &) = delete;

    /// Assignment operator
    void operator=(const ItemImage &) = delete;

    ItemImage(Game *game);

    //wxXmlNode* XmlSave(wxXmlNode* node) override;
};

#endif //PROJECT1_GAMELIB_ITEMIMAGE_H
