//
// Created by naodg on 3/6/2024.
//

#ifndef PROJECT1_DECLARATIONNOTE_H
#define PROJECT1_DECLARATIONNOTE_H

#include "Declaration.h"
#include "Game.h"


class DeclarationNote : public Declaration{
private:
    double mTolerance;
public:
    /// Default constructor (disabled)
    DeclarationNote() = delete;

    /// Copy constructor (disabled)
    DeclarationNote(const DeclarationNote &) = delete;

    /// Assignment operator
    void operator=(const DeclarationNote &) = delete;

    DeclarationNote(Game *game);

    void XmlLoad(wxXmlNode *node) override;

    /**
     * Draw this item
     * @param gp Device context to draw on
     * @param x X location
     * @param y Y location
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y) override;

};


#endif //PROJECT1_DECLARATIONNOTE_H
