/**
 * @file DeclarationNoteVisitor.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
#define PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H

#include "DeclarationVisitor.h"
#include "DeclarationNote.h"
/**
 * Class for a Note Declaration Visitor
 */
class DeclarationNoteVisitor : public DeclarationVisitor {
private:
    int mTrack = 0;
    double mTolerance = 0;
public:

    /**
     * Get track of the note
     * @return track of the note
     */
    int GetTrack() const { return mTrack; }

    /**
 * Get track of the note
 * @return track of the note
 */
    double GetTolerance() const { return mTolerance; }


    /**
    * Visit key
    * @param key The key we are visiting
    */
    void VisitDeclarationNote (DeclarationNote* note) override
    {
        mTrack = note->GetTrack();
        mTolerance = note->GetTolerance();
    }

};

#endif //PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
