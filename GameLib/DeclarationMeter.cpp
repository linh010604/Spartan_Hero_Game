/**
 * @file DeclarationMeter.cpp
 * @author thaol
 */

#include "pch.h"
#include "DeclarationMeter.h"
#include "Game.h"


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

void DeclarationMeter:: Draw(std::shared_ptr <wxGraphicsContext> gp, double x, double y)
{
    Declaration::Draw(gp, x, y);

    gp->DrawBitmap(*mNeedleBitmap,
                   int(x -this->GetWidth() / 2),
                   int(y -this->GetHeight() / 2),
                   this->GetWidth(), this->GetHeight());

    gp->DrawBitmap(*mCoverBitmap,
                   int(x -this->GetWidth() / 2),
                   int(y -this->GetHeight() / 2),
                   this->GetWidth(), this->GetHeight());
}

