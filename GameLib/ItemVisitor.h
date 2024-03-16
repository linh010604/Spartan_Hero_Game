/**
 * @file ItemVisitor.h
 * @author Linh Nguyen
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

    /**
     * Visit a ItemSoundboard object
     * @param soundboard Soundboard we are visiting
     */
    virtual void VisitItemSoundboard(ItemSoundboard* soundboard) {}

    /**
     * Visit a ItemScoreboard object
     * @param scoreboard Soundboard we are visiting
     */
    virtual void VisitItemScoreboard(ItemScoreboard* scoreboard) {}

    /**
     * Visit a ItemImage object.
     * @param image Image we are visiting.
     */
    virtual void VisitItemImage(ItemImage* image) {}

    /**
     * Visit a ItemMeter object.
     * @param meter Meter we are visiting.
     */
    virtual void VisitItemMeter(ItemMeter* image) {}

};

#endif //PROJECT1_GAMELIB_ITEMVISITOR_H
