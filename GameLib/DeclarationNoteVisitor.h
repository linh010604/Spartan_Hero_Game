/**
 * @file DeclarationNoteVisitor.h
 * @author thaol
 *
 *  Visitor to declaration note
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
#define PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H

#include "DeclarationVisitor.h"
#include "DeclarationNote.h"

/**
 * Visitor class for puck
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
     * Get tolerance of the puck
     * @return tolerance of the puck
     */
    double GetTolerance() const { return mTolerance; }

    /**
    * Visit Declaration note
    * @param note The note we are visiting
    */
    void VisitDeclarationNote (DeclarationNote* note) override
    {
        mTrack = note->GetTrack();
        mTolerance = note->GetTolerance();
    }

};

#endif //PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
