/**
 * @file ItemImage.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_ITEMIMAGE_H
#define PROJECT1_GAMELIB_ITEMIMAGE_H

#include "Item.h"

/**
 * Class for a Image Item
 */
class ItemImage : public Item {
public:
    /// Default constructor (disabled)
    ItemImage() = delete;

    /// Copy constructor (disabled)
    ItemImage(const ItemImage &) = delete;

    /// Assignment operator
    void operator=(const ItemImage &) = delete;

    ItemImage(Game *game);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitItemImage(this); }


};

#endif //PROJECT1_GAMELIB_ITEMIMAGE_H
