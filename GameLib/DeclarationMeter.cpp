/**
 * @file DeclarationMeter.cpp
 * @author thaol
 */

#include "pch.h"
#include "DeclarationMeter.h"
#include "Game.h"

using namespace std;

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
    wxString neddleFilename = ImageDir + node->GetAttribute(L"needle","");
    mCoverBitmap = make_unique<wxBitmap>(
        coverFilename, wxBITMAP_TYPE_ANY);

    Declaration::XmlLoad(node);
}