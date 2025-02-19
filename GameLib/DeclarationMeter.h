/**
 * @file DeclarationMeter.h
 * @author Linh Nguyen
 *
 * File for the Declaration Meter Class
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONMETER_H
#define PROJECT1_GAMELIB_DECLARATIONMETER_H

#include "Declaration.h"

/**
 * Meter Class derived from Declaration
 */
class DeclarationMeter : public Declaration
{
private:
    /// The bitmap we can display for this image
    std::unique_ptr<wxBitmap> mCoverBitmap;

    /// The bitmap we can display for this image
    std::unique_ptr<wxBitmap> mNeedleBitmap;

public:
    /// Default constructor (disabled)
    DeclarationMeter() = delete;

    /// Copy constructor (disabled)
    DeclarationMeter(const DeclarationMeter &) = delete;

    /// Assignment operator
    void operator=(const DeclarationMeter &) = delete;

    DeclarationMeter(Game *game);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor *visitor) override { visitor->VisitDeclarationMeter(this); }

};

#endif //PROJECT1_GAMELIB_DECLARATIONMETER_H
