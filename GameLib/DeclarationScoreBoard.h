/**
 * @file DeclarationScoreBoard.h
 * @author Linh Nguyen
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H
#define PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H

#include "Declaration.h"

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
};

#endif //PROJECT1_GAMELIB_DECLARATIONSCOREBOARD_H


