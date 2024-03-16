/**
 * @file DeclarationSoundBoard.cpp
 * @author Linh Nguyen
 */

#include "pch.h"
#include "DeclarationSoundBoard.h"
#include "Game.h"
#include "ItemKey.h"

using namespace std;

/// All images directory
wstring const ImageDir = L"images/";

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationSoundBoard::DeclarationSoundBoard(Game *game): Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationSoundBoard::XmlLoad(wxXmlNode *node)
{
    wxString coverFilename = ImageDir + node->GetAttribute(L"cover","");
    mCoverBitmap = make_unique<wxBitmap>(
        coverFilename, wxBITMAP_TYPE_ANY);

    node->GetAttribute(L"top-width", L"0").ToInt(&mTopWidth);
    node->GetAttribute(L"size-beats", L"0").ToInt(&mSizeBeats);

    Declaration::XmlLoad(node);
}

/**
 * Draw the declaration sound board on the graphics context.
 *
 * This function draws the declaration sound board represented by this instance onto the provided
 * graphics context at the specified coordinates. If the `before` parameter is true, the cover
 * image of the sound board is drawn. Otherwise, the sound board is drawn as part of the scene.
 * The sound board is positioned with its center at the specified (x, y) coordinates.
 *
 * @param gp The shared pointer to the graphics context on which to draw the sound board
 * @param x The x-coordinate where the center of the sound board will be positioned
 * @param y The y-coordinate where the center of the sound board will be positioned
 * @param before A boolean value indicating whether to draw the sound board before other elements
 */
void DeclarationSoundBoard::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before) {
    if (before)
        Declaration::Draw(gp, x, y, before);
    else
        gp->DrawBitmap(*mCoverBitmap,
                   int(x - this->GetWidth() / 2),
                   int(y - this->GetHeight() / 2),
                   this->GetWidth() , this->GetHeight());
}
