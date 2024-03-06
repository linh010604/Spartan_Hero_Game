/**
 * @file DeclarationScoreBoard.cpp
 * @author thaol
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include "DeclarationScoreBoard.h"

using namespace std;


wstring const ImageDir = L"images/score-board.png";

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationScoreBoard::DeclarationScoreBoard(Game *game): Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationScoreBoard::XmlLoad(wxXmlNode *node)
{
    wxString coverFilename = ImageDir;
    mCoverBitmap = make_unique<wxBitmap>(
        coverFilename, wxBITMAP_TYPE_ANY);

    //node->GetAttribute(L"top-width", L"0").ToInt(&mTopWidth);
    //node->GetAttribute(L"size-beats", L"0").ToInt(&mSizeBeats);

    Declaration::XmlLoad(node);
}

void DeclarationScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y) {
    Declaration::Draw(gp, x, y);

    gp->DrawBitmap(*mCoverBitmap,
                   int(x - this->GetWidth() / 2),
                   int(y - this->GetHeight() / 2),
                   this->GetWidth() , this->GetHeight());
}