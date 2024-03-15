/**
 * @file DeclarationNote.h
 * @author thaol
 * @author Naodg
 *
 *
 */

#ifndef PROJECT1_DECLARATIONNOTE_H
#define PROJECT1_DECLARATIONNOTE_H

#include "Declaration.h"
#include "Game.h"
#include "ItemKey.h"

/**
 * Class for an Declaration Note (Puck)
 */
class DeclarationNote : public Declaration{
private:
    int mTrack = 0;
    double mTolerance; ///< Tolerance of the note
public:
    /// Default constructor (disabled)
    DeclarationNote() = delete;

    /// Copy constructor (disabled)
    DeclarationNote(const DeclarationNote &) = delete;

    /// Assignment operator
    void operator=(const DeclarationNote &) = delete;

    DeclarationNote(Game *game);

    double GetTolerance() const {return mTolerance;}

    void XmlLoad(wxXmlNode *node) override;

    int GetTrack() const {return mTrack;}

    /**
     * Draw this item
     * @param gp Device context to draw on
     * @param x X location
     * @param y Y location
     */
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
