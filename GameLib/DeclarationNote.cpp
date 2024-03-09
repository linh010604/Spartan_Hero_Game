//
// Created by naodg on 3/6/2024.
//

#include "pch.h"
#include "Game.h"
#include "DeclarationNote.h"



using namespace std;

wstring const ImageDir = L"images/";


DeclarationNote::DeclarationNote(Game *game): Declaration(game)
{

}

void DeclarationNote::XmlLoad(wxXmlNode *node)
{
    Declaration::XmlLoad(node);

    node->GetAttribute(L"tolerance", L"0").ToDouble(&mTolerance);
}
void DeclarationNote::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y)
{
    Declaration::Draw(gp, x, y);
}
