/**
 * @file ItemVisitor.h
 * @author Roshni Kaur
 *
 *
 */

#ifndef PROJECT1_GAMELIB_ITEMVISITOR_H
#define PROJECT1_GAMELIB_ITEMVISITOR_H

class ItemSoundboard;
class ItemImage;
class ItemMeter;
class ItemScoreboard;

/**
 * Item visitor base class
 */
class ItemVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}
public:
    virtual ~ItemVisitor() {}



};

#endif //PROJECT1_GAMELIB_ITEMVISITOR_H