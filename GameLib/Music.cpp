/**
 * @file Music.cpp
 * @author thaol
 */

#include "pch.h"
#include "Music.h"
#include "Game.h"

using namespace std;

bool const AfterTrack = true;

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
    node->GetAttribute(L"beat", L"0").ToDouble(&mBeat);
    node->GetAttribute(L"duration", L"0").ToDouble(&mDuration);

}

void Music::Draw(std::shared_ptr<wxGraphicsContext> gp)
{
    if (mFirstUpdate && mY <= mKey->GetY2()){
        mDeclaration->Update(mY/mKey->GetY2());
        mDeclaration->Draw(gp, mX, mY, AfterTrack);
    }

}
void Music::Update(double elapsed, double timeOnTrack)
{
    double currBeat = mGame->GetAbsoluteBeat();
    double noteBeat = (mMeasure-1) * mGame->GetBeatsPerMersure() + (mBeat-1);

    if (currBeat > noteBeat)
    {
        //set initial location at top of track
        if (!mFirstUpdate)
        {
           mX = mKey->GetX1();
           mY = mKey->GetY1();
           mFirstUpdate = true;
        }
        else //set new location if already linked to track
        {
            double newPosX =mX + ((mKey->GetX2() - mKey->GetX1())/timeOnTrack)*elapsed;
            double newPosY = mY + ((mKey->GetY2() - mKey->GetY1())/timeOnTrack)*elapsed;

            mX = newPosX;
            mY = newPosY;
        }
    }
}

bool Music::HitTest(wxString key, double elapsed)
{
    if (key == mKey->GetKey() ){
        return true;
    }
    return false;
}
