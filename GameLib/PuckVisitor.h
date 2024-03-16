/**
 * @file PuckVisitor.h
 * @author Nicolas Roberts
 *
 * Puck visitor base class.
 */

#ifndef PROJECT1_PUCKVISITOR_H
#define PROJECT1_PUCKVISITOR_H

// Forward references to all item types
class ItemSoundboard;

/**
 * Visitor class for a puck
 */
class PuckVisitor {
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    PuckVisitor() {}

private:

public:
    virtual ~PuckVisitor() {}

    /**
     * Visit soundboard
     * @param soundboard The soundboard we are visiting
     */
     virtual void VisitSoundboard(ItemSoundboard* soundboard) {}

};


#endif //PROJECT1_PUCKVISITOR_H
