/**
 * @file Music.cpp
 * @author Linh Nguyen
 */

#include "pch.h"
#include "Music.h"
#include "Game.h"
#include "DeclarationNoteVisitor.h"

using namespace std;

/// Boolean constant indicating that the action occurs after the track.
bool const AfterTrack = true;

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;

/// Number representing the full points awarded for a correct action.
int FullPoint = 10;

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

/**
 *Draws the music on the graphics context.
 *
 * This function handles drawing the music note, including the long duration line if applicable, based on the current state of the note.
 *
 * @param gp A shared pointer to the wxGraphicsContext object used for drawing.
 */
void Music::Draw(std::shared_ptr<wxGraphicsContext> gp)
{
    if(mFirstUpdate && mAudio->GetLong() && mLongY < mKey->GetY2())
    {
        wxPen longDurationPen(*wxRED, LongDurationLineWidth);
        gp->SetPen(longDurationPen);
        if(mY < mKey->GetY2())
        {
            gp->StrokeLine(mLongX, mLongY, mX, mY);
        }
        else
        {
            gp->StrokeLine(mLongX, mLongY, mKey->GetX2(), mKey->GetY2());
        }
    }

    if(mFirstUpdate && mY < mKey->GetY2())
    {
        mDeclaration->Update(mY / mKey->GetY2());
        mDeclaration->Draw(gp, mX, mY, AfterTrack);
    }
}

/**
 * Updates the position of the music note.
 *
 * @param elapsed The elapsed time since the last update.
 * @param timeOnTrack The total time taken to travel the track.
 */
void Music::Update(double elapsed, double timeOnTrack)
{
    if(mGame->GetAutopPlayState())
    {
        mGame->AutoplayMusic();
    }
    double currBeat = mGame->GetAbsoluteBeat();
    double noteBeat = (mMeasure - 1) * mGame->GetBeatsPerMersure() + (mBeat - 1);

    if(!mFirstUpdate)
    {
        mX = mKey->GetX1();
        mY = mKey->GetY1();
        mLongX = mX;
        mLongY = mY;
    }

    if(currBeat > noteBeat && !mStopAtKey)
    {
        //set initial location at top of track
        if(!mFirstUpdate)
        {
            mX = mKey->GetX1();
            mY = mKey->GetY1();
            mFirstUpdate = true;
        }
        else if(mY - mKey->GetY2() > 8 && !mPlayMusic)
        {
            mContinueDurationLine = true;
            mStopAtKey = true;
            //
        }
        else //set new location if already linked to track
        {
            double newPosX = mX + ((mKey->GetX2() - mKey->GetX1()) / timeOnTrack) * elapsed;
            double newPosY = mY + ((mKey->GetY2() - mKey->GetY1()) / timeOnTrack) * elapsed;

            mX = newPosX;
            mY = newPosY;
        }

        if(mAudio->GetLong())
        {
            double longDurationLengthY = (mDuration / mGame->GetBeatsPerMersure()) * (mKey->GetY2() - mKey->GetY1());
            double longDurationLengthX = (mDuration / mGame->GetBeatsPerMersure()) * (mKey->GetX2() - mKey->GetX1());

            if(mY - longDurationLengthY > mKey->GetY1())
            {
                mLongX = mX - longDurationLengthX;
                mLongY = mY - longDurationLengthY;
            }
        }
        else
        {
            mLongX = mX;
            mLongY = mY;
        }
    }
    else if(mContinueDurationLine && mAudio->GetLong())
    {
        if(mLongY - mKey->GetY2() > 0)
        {
            mContinueDurationLine = false;
            //note->GetGame()->AddScore(MaxDurationBonus);
        }
        else //stop drawing line once top of line gets to key
        {

            mLongX = mLongX + ((mKey->GetX2() - mKey->GetX1()) / timeOnTrack) * elapsed;
            mLongY = mLongY + ((mKey->GetY2() - mKey->GetY1()) / timeOnTrack) * elapsed;

        }
    }

    DeclarationNoteVisitor declarationVisitor;
    mDeclaration->Accept(&declarationVisitor);
    double tolerance = declarationVisitor.GetTolerance();

    if(mY > mKey->GetY2() + tolerance && !mPlayMusic && !mGame->GetAutopPlayState())
    {
        mPlayMusic = true;
        mGame->UpdateTotalNote();
    }
}

/**
 * Plays the music note automatically.
 */
void Music::PlayAutoMusic()
{
    /// Auto play music (add to different function)
    if(mY != 0 && mY >= mKey->GetY2() && !mPlayMusic)
    {
        //if (mStopAtKey){
        mPlayMusic = true;
        mBeatPlay = mGame->GetAbsoluteBeat();
        mAudio->LoadSound(mGame->GetAudioEngine());
        mAudio->PlaySound();
        mGame->UpdatePlayedNote();
        mGame->GetGameStateManager()->UpdateScore(FullPoint);
//        }

    }
    else if(mBeatPlay != 0 && mPlayMusic && mGame->GetAbsoluteBeat() - mDuration > mBeatPlay)
    {
        mAudio->PlayEnd();
        mBeatPlay = 0;
    }
}

/**
 * Plays the music note automatically based on the current state.
 * If the note has reached its target position on the track, it triggers the playback of its associated audio.
 *
 * @return True if the note is currently playing its music, false otherwise.
 */
bool Music::PlayManualMusic()
{
    double currBeat = mGame->GetAbsoluteBeat();
    double noteBeat = (mMeasure - 1) * mGame->GetBeatsPerMersure() + (mBeat - 1);

    DeclarationNoteVisitor declarationVisitor;
    mDeclaration->Accept(&declarationVisitor);
    double tolerance = declarationVisitor.GetTolerance();

    double acceptedY = (tolerance / mGame->GetBeatsPerMersure()) * (mKey->GetY2() - mKey->GetY1());

    if(abs(mY - mKey->GetY2()) <= acceptedY)
    {
        mPlayMusic = true;
        mBeatPlay = mGame->GetAbsoluteBeat();
        mAudio->LoadSound(mGame->GetAudioEngine());
        mAudio->PlaySound();
        mGame->UpdatePlayedNote();
    }
    else if(mBeatPlay != 0 && mPlayMusic && mGame->GetAbsoluteBeat() - mDuration > mBeatPlay)
    {
        //mGame->GetGameStateManager()->UpdateScore(FullPoint);
        mAudio->PlayEnd();
        mBeatPlay = 0;
    }

    return mPlayMusic;
}

/**
 * Handles the key up event for the music note.
 * Stops the music playback if it's ongoing and updates the score accordingly.
 *
 * @return True if the music was playing and is now stopped, false otherwise.
 */
bool Music::KeyUp()
{
    if(mBeatPlay != 0 && mPlayMusic)
    {
        mAudio->PlayEnd();
        if(mAudio->GetLong())
        {
            int point = (mGame->GetAbsoluteBeat() - mBeatPlay) / mDuration * 10;
            mGame->GetGameStateManager()->UpdateScore(point);
        }
        else
            mGame->GetGameStateManager()->UpdateScore(FullPoint);
        mBeatPlay = 0;
    }
    return mPlayMusic;
}
