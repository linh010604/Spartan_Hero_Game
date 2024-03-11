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

class DeclarationNoteVisitor : public DeclarationVisitor {
private:
    int mTrack = 0;
public:

    /**
     * Get track of the note
     * @return track of the note
     */
    int GetTrack() const { return mTrack; }

    /**
    * Visit key
    * @param key The key we are visiting
    */
    void VisitDeclarationNote (DeclarationNote* note) override
    {
        mTrack = note->GetTrack();
    }

};

#endif //PROJECT1_GAMELIB_DECLARATIONNOTEVISITOR_H
