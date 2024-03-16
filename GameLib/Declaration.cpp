/**
 * @file Declaration.cpp
 * @author Linh Nguyen
 */

#include "pch.h"
#include "Declaration.h"
#include "Game.h"

using namespace std;

/// All images directory
wstring const ImageDir = L"images/";
// wstring const ExtraImageDir = L"ExtraImages/";

/**
 * Destructor
 */
Declaration::~Declaration()
{
}

/**
 * Constructor
 * @param game The game this declaration is a member of
 */
Declaration::Declaration(Game *game) : mGame(game)
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
void Declaration::XmlLoad(wxXmlNode *node)
{
    mId = node->GetAttribute(L"id", L"0").ToStdWstring();

    wxString filename = ImageDir + node->GetAttribute(L"image","");
    mDeclarationImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mDeclarationBitmap = make_unique<wxBitmap>(*mDeclarationImage);
    mWidth = mDeclarationBitmap->GetWidth();
    mHeight = mDeclarationBitmap->GetHeight();

    auto sizeString = node->GetAttribute("size","0,0");
    sizeString.BeforeFirst(',').ToDouble(&mWidth);
    sizeString.AfterFirst(',').ToDouble(&mHeight);
}

/**
 * Draw the declaration item on the graphics context.
 *
 * The declaration item is drawn with its center positioned at the given (x, y) coordinates.
 *
 * @param gp A shared pointer to the graphics context on which the item will be drawn.
 * @param x The x-coordinate of the center position for drawing the item.
 * @param y The y-coordinate of the center position for drawing the item.
 * @param before If true, the item is drawn before other elements; if false, it's drawn after.
 *
 */
void Declaration::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before) {
    gp->DrawBitmap(*mDeclarationBitmap,
                   int(x - mWidth*mScale / 2),
                   int(y - mHeight*mScale / 2),
                   mWidth*mScale, mHeight*mScale);
}
