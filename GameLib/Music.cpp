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

const int FullPoint = 10;

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
    if (mFirstUpdate && mAudio->GetLong() &&  mLongY < mKey->GetY2() ){
        wxPen longDurationPen(*wxRED, LongDurationLineWidth);
        gp->SetPen(longDurationPen);
        if( mY < mKey->GetY2()){
            gp->StrokeLine(mLongX, mLongY, mX, mY);
        }
        else{
            gp->StrokeLine(mLongX, mLongY, mKey->GetX2(), mKey->GetY2());
        }
    }

    if (mFirstUpdate && mY <= mKey->GetY2()){
        mDeclaration->Update(mY/mKey->GetY2());
        mDeclaration->Draw(gp, mX, mY, AfterTrack);
    }
    else if (mFirstUpdate && mY > mKey->GetY2()){
        if (!mAddedNote){
            mGame->UpdateTotalNote();
            mAddedNote = true;
        }

        mPlayMusic = true;
    }

}
void Music::Update(double elapsed, double timeOnTrack)
{
    if (mGame->GetAutopPlayState()){
        mGame->AutoplayMusic();
    }
    double currBeat = mGame->GetAbsoluteBeat();
    double noteBeat = (mMeasure-1) * mGame->GetBeatsPerMersure() + (mBeat-1);

    if (!mFirstUpdate)
    {
        mX = mKey->GetX1();
        mY = mKey->GetY1();
        mLongX = mX;
        mLongY = mY;
    }

    DeclarationNoteVisitor declarationVisitor;
    mDeclaration->Accept(&declarationVisitor);
    double tolerance = declarationVisitor.GetTolerance();
    double acceptedY = (tolerance/ mGame->GetBeatsPerMersure()) * (mKey->GetY2() - mKey->GetY1());

    if (currBeat > noteBeat && !mStopAtKey)
    {
        //set initial location at top of track
        if (!mFirstUpdate)
        {
            mX = mKey->GetX1();
            mY = mKey->GetY1();
            mFirstUpdate = true;
        }
        else if ( mY - mKey->GetY2() > 8 && !mPlayMusic){
            mContinueDurationLine = true;
            mStopAtKey = true;
        }
        else
        {
            double newPosX = mX + ((mKey->GetX2() - mKey->GetX1())/timeOnTrack)*elapsed;
            double newPosY = mY + ((mKey->GetY2() - mKey->GetY1())/timeOnTrack)*elapsed;

            mX = newPosX;
            mY = newPosY;
        }


        if(mAudio->GetLong()){
            double longDurationLengthY = (mDuration/ mGame->GetBeatsPerMersure()) * (mKey->GetY2() - mKey->GetY1());
            double longDurationLengthX = (mDuration/ mGame->GetBeatsPerMersure()) * (mKey->GetX2() - mKey->GetX1());

            if (mY - longDurationLengthY > mKey->GetY1()){
                mLongX = mX - longDurationLengthX;
                mLongY = mY - longDurationLengthY;
            }

        }
        else {
            mLongX = mX;
            mLongY = mY;
        }

    }
    else if (mContinueDurationLine && mAudio->GetLong()){
        if(mLongY - mKey->GetY2() > 0){
            mContinueDurationLine = false;
        }
        else //stop drawing line once top of line gets to key
        {

            mLongX = mLongX + ((mKey->GetX2() - mKey->GetX1())/timeOnTrack)*elapsed;
            mLongY = mLongY + ((mKey->GetY2() - mKey->GetY1())/timeOnTrack)*elapsed;

        }

    }

    if (mY >= mKey->GetY2() + acceptedY && !mPlayMusic && !mGame->GetAutopPlayState()){
        mPlayMusic = true;
    }
}

void Music::PlayAutoMusic()
{
    /// Auto play music (add to different function)
    if (mY!= 0 && mY >= mKey->GetY2() && !mPlayMusic){
        mPlayMusic = true;
        mBeatPLay = mGame->GetAbsoluteBeat();
        mAudio->LoadSound(mGame->GetAudioEngine());
        mAudio->PlaySound();
        mGame->UpdatePlayedNote();
        mGame->GetGameStateManager()->UpdateScore(FullPoint);

    }
    else if(mBeatPLay != 0 && mPlayMusic && mGame->GetAbsoluteBeat()- mDuration > mBeatPLay){
        mAudio->PlayEnd();
        mBeatPLay = 0;
    }
}
bool Music::PlayMannualMusic()
{

    DeclarationNoteVisitor declarationVisitor;
    mDeclaration->Accept(&declarationVisitor);
    double tolerance = declarationVisitor.GetTolerance();

    double acceptedY = (tolerance/ mGame->GetBeatsPerMersure()) * (mKey->GetY2() - mKey->GetY1());

    if (!mPlayMusic &&  mKey->GetY2()-mY <= acceptedY){
        mPlayMusic = true;
        mBeatPLay = mGame->GetAbsoluteBeat();
        mAudio->LoadSound(mGame->GetAudioEngine());
        mAudio->PlaySound();
        mGame->UpdatePlayedNote();
        mGame->GetGameStateManager()->UpdateScore(FullPoint);
    }
    else if (mBeatPLay != 0 && mPlayMusic && mGame->GetAbsoluteBeat()- mDuration > mBeatPLay){
        mAudio->PlayEnd();
        mBeatPLay = 0;
        if (mAudio->GetLong()){
            mGame->GetGameStateManager()->UpdateScore(FullPoint);
        }
    }

    return mPlayMusic;
}
bool Music::KeyUp()
{
    if (mBeatPLay != 0 && mPlayMusic){
        mAudio->PlayEnd();
        if (mAudio->GetLong()){
            int point  = (mGame->GetAbsoluteBeat() - mBeatPLay)/mDuration*10;
            mGame->GetGameStateManager()->UpdateScore(point);
        }

        mBeatPLay = 0;
    }
    return mPlayMusic;
}


