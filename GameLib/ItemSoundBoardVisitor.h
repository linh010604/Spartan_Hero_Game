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

class ItemSoundBoardVisitor : public ItemVisitor {
private:
    int mTrack;
    std::shared_ptr<ItemKey> mKey;

public:
    ItemSoundBoardVisitor(int track) : mTrack(track) {}

    /**
    * Visit key
    * @param key The key we are visiting
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
