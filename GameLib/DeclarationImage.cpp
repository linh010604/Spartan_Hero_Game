/**
 * @file DeclarationImage.cpp
 * @author thaol
 */

#include "pch.h"
#include "DeclarationImage.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationImage::DeclarationImage(Game *game): Declaration(game)
{
}

///**
// * Save this declaration to an XML node
// * @param node The parent node we are going to be a child of
// * @return
// */
//wxXmlNode* FishBeta::XmlSave(wxXmlNode* node)
//{
//    auto itemNode = Fish::XmlSave(node);
//    itemNode->AddAttribute(L"type", L"beta");
//
//    return itemNode;
//}