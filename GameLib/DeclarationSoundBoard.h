/**
 * @file DeclarationSoundBoard.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONSOUNDBOARD_H
#define PROJECT1_GAMELIB_DECLARATIONSOUNDBOARD_H

#include "Declaration.h"

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
     * Draw this item
     * @param dc Device context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y);
};

#endif //PROJECT1_GAMELIB_DECLARATIONSOUNDBOARD_H
