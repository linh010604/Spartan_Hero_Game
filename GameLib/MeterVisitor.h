/**
 * @file MeterVisitor.h
 * @author Roshni Kaur
 *
 *
 */

#ifndef PROJECT1_GAMELIB_METERVISITOR_H
#define PROJECT1_GAMELIB_METERVISITOR_H

class ItemSoundboard;

class MeterVisitor{
protected:
    /**
    * Constructor
    * Ensures this is an abstract class
    */


private:

public:
    virtual ~MeterVisitor () {}
    /**
    * Visit soundboard
    * @param soundboard The soundboard we are visiting
    */
    virtual void VisitSoundboard (ItemSoundboard* soundboard) {}


};

#endif //PROJECT1_GAMELIB_METERVISITOR_H
