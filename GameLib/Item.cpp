/**
 * @file Item.cpp
 * @author Naod Ghebredngl
 * The item class used to store the items used in the game
 */

#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{

}

/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game) : mGame(game)
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    auto position = node->GetAttribute("p","0,0");
    position.BeforeFirst(',').ToDouble(&mX);
    position.AfterFirst(',').ToDouble(&mY);
    mId = node->GetAttribute(L"id", L"0").ToStdWstring();
}

/**
 * Draw this item
 * @param gp Device context to draw on
 * @param declaration The corresponding declaration
 * @param beforeSoundboard Check if this item is draw above or below
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> declaration, bool beforeSoundboard)
{

}
