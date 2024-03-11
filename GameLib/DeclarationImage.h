/**
 * @file DeclarationImage.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONIMAGE_H
#define PROJECT1_GAMELIB_DECLARATIONIMAGE_H

#include "Declaration.h"

/**
 * Class for an Image Declaration
 */
class DeclarationImage : public Declaration {
public:
    /// Default constructor (disabled)
    DeclarationImage() = delete;

    /// Copy constructor (disabled)
    DeclarationImage(const DeclarationImage &) = delete;

    /// Assignment operator
    void operator=(const DeclarationImage &) = delete;

    DeclarationImage(Game *game);

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitDeclarationImage(this); }

};

#endif //PROJECT1_GAMELIB_DECLARATIONIMAGE_H
