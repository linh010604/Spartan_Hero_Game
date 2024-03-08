/**
 * @file ItemKey.cpp
 * @author Naod Ghebredngl
 *
 */

#include "pch.h"
#include "ItemKey.h"
#include "Game.h"

using namespace std;

/// All images directory
wstring const ImageDir = L"images/";


/**
 * Constructor
 * @param soundboard The soundboard this track is a member of
 */
ItemKey::ItemKey(ItemSoundBoard *soundboard) : mItemSoundBoard(soundboard)
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
void ItemKey::XmlLoad(wxXmlNode *node)
{
    auto size = node->GetAttribute("key-size","0,0");
    size.BeforeFirst(',').ToDouble(&mWidth);
    size.AfterFirst(',').ToDouble(&mHeight);
    node->GetAttribute(L"track", L"0").ToInt(&mTrack);
    mKey = node->GetAttribute(L"key", L"").ToStdWstring();
    wxString filename = ImageDir + node->GetAttribute(L"key-image","");
    mKeyBitmap = make_unique<wxBitmap>(filename, wxBITMAP_TYPE_ANY);
}

/**
 * Draw this item
 * @param gp Device context to draw on
 * @param x X position
 * @param y Y position
 */
void ItemKey::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y) {
    gp->DrawBitmap(*mKeyBitmap,
                   int(x - mWidth / 2),
                   int(y - mHeight / 2),
                   mWidth, mHeight);
}
