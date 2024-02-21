//
// Created by naodg on 2/21/2024.
//


#include "pch.h"
#include "Item.h"
#include "Game.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item() {
    // Cleanup code, if needed
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
    // Existing drawing implementation should be fine.
    // Adjust if your game has specific rendering needs.
}
