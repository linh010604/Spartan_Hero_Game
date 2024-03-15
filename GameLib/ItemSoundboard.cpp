/**
 * @file ItemSoundboard.cpp
 * @author Nicolas Roberts
 * @author Linh Nguyen
 *
 */

#include "pch.h"
#include "ItemSoundboard.h"
#include "ItemKey.h"
#include "Game.h"
#include <memory>

using namespace std;

/// Width of the track line. The line is
/// drawn a wxBLACK.
const int TrackLineWidth = 5;

/// The maximum number of tracks
const int MaxTracks = 10;

/// The minimum number of tracks
const int MinTracks = 8;

/// What is the border of the left and right
/// of the tracks? This is the percentage of
/// the space to the left of the first track line
/// and to the right of the last track line
const double Border = 0.075;

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

/// Percentage down on the soundboard to the keys
/// This is where the pucks go under the key and
/// disappear.
const double KeyRow = 0.85;

/**
 * Constructor
 * @param game The game this item is a member of
 */
ItemSoundboard::ItemSoundboard(Game *game) : Item(game)
{
}


/**
 * Add track to soundboard
 * @param track New track to add
 */
void ItemSoundboard::AddTrack(std::shared_ptr<ItemKey> track)
{
    mKeys.push_back(track);
}

/**
 * Load the attributes for Soundboard node.
 * @param node The Xml node we are loading the declaration from
 */
void ItemSoundboard::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    mKeys.clear();
    auto soundnode = node-> GetChildren();
    for(*soundnode ; soundnode; soundnode=soundnode->GetNext())
    {
        shared_ptr<ItemKey> track = make_shared<ItemKey>(this);
        track->XmlLoad(soundnode);
        AddTrack(track);
    }
}

/**
 * Draw the track line and keys
 * @param gp A shared pointer to a wxGraphicsContext object used for drawing.
 * @param soundboard item soundboard with location of the track
 * @param beforeSoundboard check if this function is draw on top or bottom
 */
void ItemSoundboard::Draw(std::shared_ptr<wxGraphicsContext> gp, std::shared_ptr<Declaration> soundboard, bool beforeSoundboard)
{
    int tracksCount = mKeys.size();
    if (beforeSoundboard) {
        double WidthSoundBoard = soundboard->GetWidth();
        double HeightSoundBoard = soundboard->GetHeight();
        double TopWidthSoundBoard = soundboard->GetTopWidth();

        // Draw tracks
        wxPen linePen(*wxBLACK, TrackLineWidth);
        gp->SetPen(linePen);

        // Find length of soundboard at KeyRow and TopClearance
        double soundBoardLengthAtX1Init = ((WidthSoundBoard-TopWidthSoundBoard)/HeightSoundBoard)*(HeightSoundBoard*TopClearance) + TopWidthSoundBoard;
        double soundBoardLengthAtX2Init = ((WidthSoundBoard-TopWidthSoundBoard)/HeightSoundBoard)*(HeightSoundBoard*KeyRow) + TopWidthSoundBoard;

        // X1 and X2 for leftmost and rightmost track
        double x1InitLeftTrack = (GetX()-(soundBoardLengthAtX1Init/2)) + (soundBoardLengthAtX1Init*Border);
        double x2InitLeftTrack = (GetX()-(soundBoardLengthAtX2Init/2)) + (soundBoardLengthAtX2Init*Border);

        double x1InitRightTrack = (GetX()+(soundBoardLengthAtX1Init/2)) - (soundBoardLengthAtX1Init*Border);
        double x2InitRightTrack = (GetX()+(soundBoardLengthAtX2Init/2)) - (soundBoardLengthAtX2Init*Border);

        // Y1 and Y2 for all tracks
        double overlapCorrection = 7; // track is too long otherwise
        double y1Track = (GetY()-(HeightSoundBoard/2)) + (HeightSoundBoard*TopClearance) + overlapCorrection;
        double y2Track = (GetY()-(HeightSoundBoard/2)) + (HeightSoundBoard*KeyRow);

        // Space between each track
        double x1Space = (x1InitRightTrack - x1InitLeftTrack)/(MaxTracks - 1);
        double x2Space = (x2InitRightTrack - x2InitLeftTrack)/(MaxTracks - 1);

        double shiftX1 = 0;
        double shiftX2 = 0;
        for (int i = 0; i < tracksCount; ++i)
        {
            if(i == tracksCount/2 && tracksCount == MinTracks)
            {
                shiftX1 += 2*x1Space;
                shiftX2 += 2*x2Space;
            }

            gp->SetPen(linePen);

            gp->StrokeLine(x1InitLeftTrack + shiftX1,
                           y1Track,
                           x2InitLeftTrack + shiftX2,
                           y2Track);

            mKeys[i]->SetLocation(x1InitLeftTrack + shiftX1,x2InitLeftTrack + shiftX2,y1Track, y2Track);
            this->GetGame()->DrawNote(gp);
            shiftX1 += x1Space;
            shiftX2 += x2Space;

        }
    }
    else{
        for (int i = 0; i < tracksCount; ++i)
        {

            mKeys[i]->Draw(gp);

        }
    }

}

/**
 * Find the key of the given track
 * @param track the given track
 * @return key having the same track
 */
std::shared_ptr<ItemKey> ItemSoundboard::SearchKey(int track)
{
    for (auto key : mKeys)
    {
        if (key->GetTrack() == track)
        {
            return key;
        }
    }

    return nullptr;
}
