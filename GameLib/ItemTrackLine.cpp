/**
 * @file ItemTrackLine.cpp
 * @author Nicolas Roberts
 */

#include "pch.h"
#include "ItemTrackLine.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param soundboard The soundboard this track is a member of
 */
ItemTrackLine::ItemTrackLine(ItemSoundboard *soundboard, double x1, double y1, double x2, double y2, int track) : mItemSoundBoard(soundboard)
{
    mX1 = x1;
    mX2 = x2;
    mY1 = y1;
    mY2 = y2;
    mTrack = track;
}

void ItemTrackLine::Draw(std::shared_ptr<wxGraphicsContext> gp)
{
    gp->StrokeLine(mX1, mY1, mX2, mY2);
}