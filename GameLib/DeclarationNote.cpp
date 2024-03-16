/**
 * @file DeclarationNote.cpp
 * @author Naod Ghebredngl
 */

#include "pch.h"
#include "Game.h"
#include "DeclarationNote.h"

using namespace std;

///Image directory
wstring const ImageDir = L"images/";

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationNote::DeclarationNote(Game *game) : Declaration(game)
{
}

/**
 * Load attributes from an XML node.
 *
 * This function loads attributes from the provided XML node, such as id, image, size, tolerance,
 * and track, and initializes the corresponding member variables of the DeclarationNote object.
 * Subclasses may override this function to load additional or different attributes specific
 * to their type of declaration.
 *
 * @param node The XML node from which to load attributes
 */
void DeclarationNote::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);

    node->GetAttribute(L"tolerance", L"0").ToDouble(&mTolerance);
    node->GetAttribute(L"track", L"0").ToInt(&mTrack);
}

/**
 * Draw the declaration note on the graphics context.
 *
 * This function draws the declaration note represented by this instance onto the provided
 * graphics context at the specified coordinates. The note is positioned with its center
 * at the specified (x, y) coordinates.
 *
 * @param gp The shared pointer to the graphics context on which to draw the note
 * @param x The x-coordinate where the center of the note will be positioned
 * @param y The y-coordinate where the center of the note will be positioned
 * @param before A boolean value indicating whether to draw the note before other elements
 */
void DeclarationNote::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before)
{
    Declaration::Draw(gp, x, y, before);
}

/**
 * Update the scale of the declaration note.
 *
 * This function updates the scale of the declaration note based on the provided factor.
 * The scale affects the size of the note when drawn on the graphics context.
 *
 * @param scale The scale factor to apply to the note
 */
void DeclarationNote::Update(double scale)
{
    this->SetScale(scale);
}
