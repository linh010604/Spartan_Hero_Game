/**
 * @file DeclarationSoundBoard.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONSOUNDBOARD_H
#define PROJECT1_GAMELIB_DECLARATIONSOUNDBOARD_H

#include "Declaration.h"

/**
 * Class for a Soundboard Declaration
 */
class DeclarationSoundBoard : public Declaration
{
private:
    /// beats size
    int mSizeBeats;

    /// top width
    int mTopWidth;

    /// The bitmap we can display for this soundboard
    std::unique_ptr<wxBitmap> mCoverBitmap;

public:
    /// Default constructor (disabled)
    DeclarationSoundBoard() = delete;

    /// Copy constructor (disabled)
    DeclarationSoundBoard(const DeclarationSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const DeclarationSoundBoard &) = delete;

    DeclarationSoundBoard(Game *game);

    void XmlLoad(wxXmlNode *node) override;

    /**
     * The top width of the soundboard
     * @return top width of the soundboard
     */
    double GetTopWidth() override {return mTopWidth;}

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
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitDeclarationSoundBoard(this); }
};

#endif //PROJECT1_GAMELIB_DECLARATIONSOUNDBOARD_H
