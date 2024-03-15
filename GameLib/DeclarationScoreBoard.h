/**
 * @file DeclarationScoreBoard.h
 * @author Linh Nguyen
 * @author Angelina Jolie Daoud
 *
 * File for the Declaration Scoreboard Class
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H
#define PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H

#include "Declaration.h"
#include "GameStateManager.h"

/**
 * Scoreboard Class derived from Declaration
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
    void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(DeclarationVisitor* visitor) override { visitor->VisitDeclarationScoreBoard(this); }
private:
    std::unique_ptr<wxBitmap> mCoverBitmap;

    std::string mText = "Placeholder";

    int mScore = 000000;

};

#endif //PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H


