/**
 * @file Music.cpp
 * @author thaol
 */

#include "pch.h"
#include "Music.h"
#include "Game.h"

using namespace std;

/**
 * Destructor
 */
Music::~Music()
{

}

/**
 * Constructor
 * @param game The game this item is a member of
 */
Music::Music(Game *game) : mGame(game)
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Music::XmlLoad(wxXmlNode *node)
{
    mId = node->GetAttribute(L"id", L"0").ToStdWstring();
    mSound = node->GetAttribute(L"sound", L"").ToStdWstring();
    node->GetAttribute(L"measure", L"0").ToInt(&mMeasure);
    node->GetAttribute(L"beat", L"0").ToInt(&mBeat);
    node->GetAttribute(L"duration", L"0").ToDouble(&mDuration);

}
