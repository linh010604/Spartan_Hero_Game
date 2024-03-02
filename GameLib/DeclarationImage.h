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
 * Class for a fish of type Beta
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

//    wxXmlNode* XmlSave(wxXmlNode* node) override;

};

#endif //PROJECT1_GAMELIB_DECLARATIONIMAGE_H
