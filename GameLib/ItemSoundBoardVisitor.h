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
 * Visitor class for the soundboard
 */
class ItemSoundBoardVisitor : public ItemVisitor {
private:
    /// The given track
    int mTrack;
    /// The key match with the track given
    std::shared_ptr<ItemKey> mKey;

public:
    /**
     * Constructor
     * @param track the given track for searching
     */
    ItemSoundBoardVisitor(int track) : mTrack(track) {}

    /**
    * Visit soundboard
    * @param soundboard The item soundboard we are visiting
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
