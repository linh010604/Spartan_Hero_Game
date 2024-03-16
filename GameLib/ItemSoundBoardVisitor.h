/**
 * @file ItemSoundBoardVisitor.h
 * @author Roshni Kaur
 *
 *
 */

#ifndef PROJECT1_GAMELIB_ITEMSOUNDBOARDVISITOR_H
#define PROJECT1_GAMELIB_ITEMSOUNDBOARDVISITOR_H

#include "ItemVisitor.h"
#include "ItemKey.h"
#include "ItemSoundboard.h"
/**
 * Class for a Soundboard Visitor
 */
class ItemSoundBoardVisitor : public ItemVisitor {
private:
    int mTrack; ///< Number of Tracks
    std::shared_ptr<ItemKey> mKey; ///< The Item Keys

public:
    /**
     * Visitor for Soundboard
     * @param track The number of tracks
     */
    ItemSoundBoardVisitor(int track) : mTrack(track) {}

    /**
    * Visit key
    * @param soundboard The soundboard we are visiting
    */
    void VisitItemSoundboard (ItemSoundboard* soundboard) override
    {
        mKey = soundboard->SearchKey(mTrack);
    }

    /**
     * Get key of the track
     * @return key of the track
     */
    std::shared_ptr<ItemKey> GetKey() const { return mKey; }

};

#endif //PROJECT1_GAMELIB_ITEMSOUNDBOARDVISITOR_H
