/**
 * @file DeclarationNote.cpp
 * @author thaol
 * @author Naodg
 *
 *
 */

#include "pch.h"
#include "Game.h"
#include "DeclarationNote.h"

using namespace std;

/// All images directory
wstring const ImageDir = L"images/";


DeclarationNote::DeclarationNote(Game *game): Declaration(game)
{

}

void DeclarationNote::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);

    node->GetAttribute(L"tolerance", L"0").ToDouble(&mTolerance);
    node->GetAttribute(L"track", L"0").ToInt(&mTrack);
}
void DeclarationNote::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before)
{
    Declaration::Draw(gp, x, y,before);
}
void DeclarationNote::Update(double scale)
{
    this->SetScale(scale);
}
