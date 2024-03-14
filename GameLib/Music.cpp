/**
 * @file Music.cpp
 * @author thaol
 */

#include "pch.h"
#include "Music.h"
#include "Game.h"
#include "DeclarationNoteVisitor.h"

using namespace std;

bool const AfterTrack = true;

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;

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
Music::Music(Game *game, const std::shared_ptr<Sound> &audio) : mGame(game), mAudio(audio)
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
//    if (mFirstUpdate && mAudio->GetLong() && mPLayMusic&&  mGame->GetAbsoluteBeat() - mDuration <= mBeatPLay){
//        wxPen longDurationPen(*wxRED, LongDurationLineWidth);
//        gp->SetPen(longDurationPen);
//        gp->StrokeLine(mX, mY, mLongX, mLongY);
//    }

    if (mFirstUpdate && mY <= mKey->GetY2()){

        mDeclaration->Update(mY/mKey->GetY2());
        mDeclaration->Draw(gp, mX, mY, AfterTrack);
    }

}
void Music::Update(double elapsed, double timeOnTrack)
{
    double currBeat = mGame->GetAbsoluteBeat();
    double noteBeat = (mMeasure-1) * mGame->GetBeatsPerMersure() + (mBeat-1);

    if (currBeat >= noteBeat)
    {
        //set initial location at top of track
        if (!mFirstUpdate)
        {
           mX = mKey->GetX1();
           mY = mKey->GetY1();
           mLongX = mX;
           mLongY = mY;
           mFirstUpdate = true;
        }
        else if (mY > mKey->GetY2())//set new location if already linked to track
        {
            mContinueDurationLine = true;
            mX = mKey->GetX2();
            mY = mKey->GetY2();
        }
        else
        {
            double newPosX =mX + ((mKey->GetX2() - mKey->GetX1())/timeOnTrack)*elapsed;
            double newPosY = mY + ((mKey->GetY2() - mKey->GetY1())/timeOnTrack)*elapsed;
            mX = newPosX;
            mY = newPosY;

        }


        if (mAudio->GetLong()){
            double longDurationLengthY = mDuration/4 * (mKey->GetY2()-mKey->GetY1());
            double longDurationLengthX = mDuration/4 * (mKey->GetX2()-mKey->GetX1());
            if (mY - longDurationLengthY > mKey->GetY1()){
                mLongX = mX - longDurationLengthX;
                mLongY = mY - longDurationLengthY;
            }

        }
        else {
            mLongX = mX;
            mLongY = mY;
        }

        // Autoplay sound
        if (mY >= mKey->GetY2() && !mPLayMusic){
            mPLayMusic = true;
            mBeatPLay = currBeat;

            if (mGame->GetAutopPlayState()){
                mAudio->LoadSound(mGame->GetAudioEngine());
                mAudio->PlaySound();
            }

        }
        else if(mPLayMusic && currBeat - mDuration > mBeatPLay){
            mAudio->PlayEnd();
        }
    }
    else if (mContinueDurationLine && mAudio->GetLong()){
        if (mLongY > mKey->GetY2()){
            mLongX = mKey->GetX2();
            mLongY = mKey->GetY2();
            mContinueDurationLine = false;
        }
        else{
            mLongX = mLongX + ((mKey->GetX2() - mKey->GetX1())/timeOnTrack)*elapsed;
            mLongY = mLongY + ((mKey->GetY2() - mKey->GetY1())/timeOnTrack)*elapsed;
        }
    }

    DeclarationNoteVisitor declarationVisitor;
    mDeclaration->Accept(&declarationVisitor);
    double tolerance = declarationVisitor.GetTolerance();

    if (mY > mKey->GetY2() + tolerance && !mPlayMusic && !mGame->GetAutopPlayState()){
        mPlayMusic = true;
        mGame->UpdateTotalNote();
    }


}

bool Music::HitTest(wxString key, double elapsed)
{
    if (key == mKey->GetKey() ){
        return true;
    }
    return false;
}
