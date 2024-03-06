/**
 * @file DeclarationScoreBoard.h
 * @author Linh Nguyen
 * @author Angelina Jolie Daoud
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H
#define PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H

#include "Declaration.h"

/**
 * Class for a Scoreboard Declaration
 */
class DeclarationScoreBoard : public Declaration
{
public:
    /// Default constructor (disabled)
    DeclarationScoreBoard() = delete;

    /// Copy constructor (disabled)
    DeclarationScoreBoard(const DeclarationScoreBoard &) = delete;

    /// Assignment operator
    void operator=(const DeclarationScoreBoard &) = delete;

    DeclarationScoreBoard(Game *game);


    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y) override;
private:
    std::unique_ptr<wxBitmap> mCoverBitmap;

    std::string mText = "Placeholder";


};

#endif //PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H


