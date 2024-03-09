/**
 * @file Item.h
 * @author Naod Ghebredngl
 * file for the item class
 */

#ifndef PROJECT1_ITEM_H
#define PROJECT1_ITEM_H
#include <wx/xml/xml.h>
#include "Declaration.h"
#include "ItemVisitor.h"

/**
 * Allows access to Game without creating a circular dependency.
 */
class Game;

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

    wxString  mId = L"";  ///< Id of the declaration


protected:
    Item(Game *game);
public:
    virtual ~Item();
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
     * The Id of the item
     * @return Id
     */
    wxString GetId() const { return mId; }

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game *GetGame() { return mGame;  }

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

    virtual void XmlLoad(wxXmlNode *node);

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> declaration);

    /**
    * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(ItemVisitor* visitor) = 0;

    ///  Handle updates for animation
    /// @param elapsed The time since the last update
    virtual void Update(double elapsed) {}

};



#endif //PROJECT1_ITEM_H
