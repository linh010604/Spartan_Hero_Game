//
// Created by naodg on 2/21/2024.
//

/**
 * @file Item.h
 * @author Naod Ghebredngl
 * file for the item class
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H


#include "Game.h"

using namespace std;

/**
 * @file Item.h
 * @author Naod Ghebredngl
 *
 */

class Aquarium;



/**
 * Base class for any item in our game.
 */
class Item {
private:


/// The game this item is contained in
    Game   *mGame;

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item






protected:
    Item(Game *game, const wstring &filename);
public:
    ~Item();
    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }


    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;



    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    virtual void Draw(wxDC *dc);



    /// The underlying item image
    std::unique_ptr<wxImage> mItemImage;
    /// The bitmap we can display for the item
    std::unique_ptr<wxBitmap> mItemBitmap;
};



#endif //PROJECT1_ITEM_H
