/**
 * @file SoundBoardVisitor.h
 * @author Roshni Kaur
 *
 *
 */

#ifndef PROJECT1_GAMELIB_SOUNDBOARDVISITOR_H
#define PROJECT1_GAMELIB_SOUNDBOARDVISITOR_H

#include "ItemVisitor.h"

class ItemKey;

class SoundBoardVisitor : public ItemVisitor {
private:

public:
    virtual  ~SoundBoardVisitor() {}

    /**
    * Visit key
    * @param key The key we are visiting
    */

    void VisitItemSoundboard (ItemSoundboard* soundboard) override;

};

#endif //PROJECT1_GAMELIB_SOUNDBOARDVISITOR_H
