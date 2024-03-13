/**
 * @file DeclarationMeter.cpp
 * @author thaol
 */

#include "pch.h"
#include "DeclarationMeter.h"
#include "Game.h"

/// Positive or negative rotations of this amount will move
/// the needle to the limit in that direction.
/// A meter score of 0 will be a rotation of -0.9
/// A meter score of 100% (11) will be a rotation of 0.9
const double MaxNeedleRotation = 0.9;

/// This is how far down the need image the pivot point is
/// as a percentage of the height of the image.
const double NeedlePivotYOffset = 0.80;


using namespace std;

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

void DeclarationMeter:: Draw(std::shared_ptr <wxGraphicsContext> gp, double x, double y, bool before)
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

