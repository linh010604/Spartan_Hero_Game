/**
 * @file DeclarationNoteVisitor.h
 * @author Linh Nguyen
 *
 * File for the Declaration Note Visitor Class
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
#define PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H

#include "DeclarationVisitor.h"
#include "DeclarationNote.h"

/**
 * Note Visitor Class derived from DeclarationVisitor
 */
class DeclarationNoteVisitor : public DeclarationVisitor
{
private:
    int mTrack = 0; ///< Number of Tracks
    double mTolerance = 0; ///< Tolerance of the note
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
    * @param note The note we are visiting
    */
    void VisitDeclarationNote(DeclarationNote *note) override
    {
        mTrack = note->GetTrack();
        mTolerance = note->GetTolerance();
    }

};

#endif //PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
