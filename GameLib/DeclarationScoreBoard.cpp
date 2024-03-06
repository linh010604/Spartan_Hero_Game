/**
 * @file DeclarationScoreBoard.cpp
 * @author thaol
 */

#include "pch.h"
#include "DeclarationScoreBoard.h"
#include "Game.h"

using namespace std;

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationScoreBoard::DeclarationScoreBoard(Game *game): Declaration(game)
{
}
void DeclarationScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y)
{
    Declaration::Draw(gp, x, y);

}
