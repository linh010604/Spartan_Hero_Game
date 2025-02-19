/**
 * @file DeclarationMeter.cpp
 * @author Linh Nguyen
 */

#include "pch.h"
#include "DeclarationMeter.h"
#include "Game.h"

using namespace std;

/// Positive or negative rotations of this amount will move
/// the needle to the limit in that direction.
/// A meter score of 0 will be a rotation of -0.9
/// A meter score of 100% (11) will be a rotation of 0.9
const double MaxNeedleRotation = 0.9;

/// This is how far down the need image the pivot point is
/// as a percentage of the height of the image.
const double NeedlePivotYOffset = 0.80;

/// All images directory
wstring const ImageDir = L"images/";

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationMeter::DeclarationMeter(Game *game): Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationMeter::XmlLoad(wxXmlNode *node)
{
    wxString coverFilename = ImageDir + node->GetAttribute(L"cover","");
    mCoverBitmap = make_unique<wxBitmap>(
        coverFilename, wxBITMAP_TYPE_ANY);
    wxString needleFilename = ImageDir + node->GetAttribute(L"needle","");
    mNeedleBitmap = make_unique<wxBitmap>(
        needleFilename, wxBITMAP_TYPE_ANY);

    Declaration::XmlLoad(node);
}

/**
 * Draw the declaration meter on the graphics context.
 *
 * This function draws the declaration meter represented by this instance onto the provided
 * graphics context at the specified coordinates. The meter consists of a background image,
 * a needle indicating the current progress, and a cover image. The needle's rotation is
 * calculated based on the ratio of played notes to total notes, with adjustments made to
 * ensure the needle remains within predefined bounds. The meter is positioned with its center
 * at the specified (x, y) coordinates.
 *
 * @param gp The shared pointer to the graphics context on which to draw the meter
 * @param x The x-coordinate where the center of the meter will be positioned
 * @param y The y-coordinate where the center of the meter will be positioned
 * @param before A boolean value indicating whether to draw the meter before other elements
 */
void DeclarationMeter::Draw(std::shared_ptr <wxGraphicsContext> gp, double x, double y, bool before)
{
    Declaration::Draw(gp, x, y, before);

    int wid = this->GetWidth();
    int hit = this->GetHeight();
    int needlePivotY = (int)(hit * NeedlePivotYOffset);

    gp->PushState();
    gp->Translate(x, y + needlePivotY - hit/2);
    double playedNote = this->GetGame()->GetPlayedNote();
    double totalNote = this->GetGame()->GetTotalNote();

    if (totalNote == 0){
        gp->Rotate(MaxNeedleRotation);
        gp->DrawBitmap(*mNeedleBitmap,
                       -wid/2,
                       -needlePivotY,
                       wid, hit);
    }
    else{
        gp->Rotate( min(-MaxNeedleRotation + playedNote/totalNote * 2 * MaxNeedleRotation,MaxNeedleRotation));
        gp->DrawBitmap(*mNeedleBitmap,
                       -wid/2,
                       -needlePivotY,
                       wid, hit);
    }

    gp->PopState();

    gp->DrawBitmap(*mCoverBitmap,
                   int(x -this->GetWidth() / 2),
                   int(y -this->GetHeight() / 2),
                   this->GetWidth(), this->GetHeight());
}
