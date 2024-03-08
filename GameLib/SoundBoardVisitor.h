/**
 * @file SoundBoardVisitor.h
 * @author Roshni Kaur
 *
 *
 */

#ifndef PROJECT1_GAMELIB_SOUNDBOARDVISITOR_H
#define PROJECT1_GAMELIB_SOUNDBOARDVISITOR_H

class ItemKey;

class SoundBoardVisitor{

protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
     SoundBoardVisitor() {}

private:

public:
    virtual  ~SoundBoardVisitor() {}

    /**
    * Visit key
    * @param key The key we are visiting
    */

    //virtual void VisitSoundboard (ItemKey* soundboard) {}

};

#endif //PROJECT1_GAMELIB_SOUNDBOARDVISITOR_H
