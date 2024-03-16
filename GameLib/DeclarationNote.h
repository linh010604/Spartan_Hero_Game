/**
 * @file DeclarationNote.h
 * @author Naod Ghebredngl
 *
 * File for the Declaration Note Class
 */

#ifndef PROJECT1_DECLARATIONNOTE_H
#define PROJECT1_DECLARATIONNOTE_H

#include "Declaration.h"
#include "Game.h"
#include "ItemKey.h"

/**
 * Note Class derived from Declaration
 */
class DeclarationNote : public Declaration{
private:
    int mTrack = 0; ///< Number of tracks
    double mTolerance; ///< Tolerance of the note
public:
    /// Default constructor (disabled)
    DeclarationNote() = delete;

    /// Copy constructor (disabled)
    DeclarationNote(const DeclarationNote &) = delete;

    /// Assignment operator
    void operator=(const DeclarationNote &) = delete;

    DeclarationNote(Game *game);

    /**
     *This method returns the tolerance value used for some operation.
     * @return The tolerance value as a double.
     */
    double GetTolerance() const {return mTolerance;}

    void XmlLoad(wxXmlNode *node) override;

    /**
     * Retrieves the track number associated with this object.
     * @return The track number as an integer.
     */
    int GetTrack() const {return mTrack;}

    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitDeclarationNote(this); }

    ///  Handle updates for animation
    /// @param elapsed The time since the last update
    void Update(double elapsed) override;

};


#endif //PROJECT1_DECLARATIONNOTE_H
