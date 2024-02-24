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
 * @param filename Image file name for the item
 */
Item::Item(Game *game, const std::wstring &filename) : mGame(game) {
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}

void Item::Draw(wxDC *dc) {
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    dc->DrawBitmap(*mItemBitmap,
                   int(GetX() - wid / 2),
                   int(GetY() - hit / 2));
}
