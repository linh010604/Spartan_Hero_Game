/**
 * @file ItemSoundboard.cpp
 * @author Nicolas Roberts
 * @author Linh Nguyen
 *
 */

#include "pch.h"
#include "ItemSoundboard.h"
#include "Track.h"
#include <memory>

using namespace std;

/// Width of the track line. The line is
/// drawn a wxBLACK.
const int TrackLineWidth = 5;

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;

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
ItemSoundBoard::ItemSoundBoard(Game *game) : Item(game)
{
    //initialize Image info here

}

/**
 * Add track to soundboard
 * @param track New track to add
 */
void ItemSoundBoard::AddTrack(std::shared_ptr<Track> track)
{
    mTracks.push_back(track);
}

/**
 * Load the attributes for Soundboard node.
 * @param node The Xml node we are loading the declaration from
 */
void ItemSoundBoard::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);
    mTracks.clear();
    auto soundnode = node-> GetChildren();
    for(*soundnode ; soundnode; soundnode=soundnode->GetNext())
    {
        shared_ptr<Track> track = make_shared<Track>(this);
        track->XmlLoad(soundnode);
        AddTrack(track);
    }
}

/**
 *
 */