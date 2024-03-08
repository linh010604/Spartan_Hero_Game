/**
 * @file DeclarationScoreBoard.cpp
 * @author thaol
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include "DeclarationScoreBoard.h"
#include "GameStateManager.h"


using namespace std;


wstring const ImageDir = L"images/";

/// Font size to use to display the score
const int ScoreSize = 30;

/// Y location to display the score
/// relative to the vertical center of the scoreboard.
const int ScoreY = 15;

const int ReadyY = -10;

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

    if(gp == nullptr) return;


    // Set the font for drawing the "Get Ready" text
    wxFont font(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gp->SetFont(font, *wxBLACK);

    // Measure the text size
    double textWidth, textHeight;
    gp->GetTextExtent(mText, &textWidth, &textHeight, nullptr, nullptr);

    // Calculate the position for the text to be centered on the scoreboard
    double textX = x - textWidth / 2;
    double textY = y - textHeight / 2 + ReadyY;

    // Draw the "Get Ready" text on the scoreboard
    gp->DrawText(mText, textX, textY);

    // Set the font for drawing the score
    wxFont scoreFont(ScoreSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gp->SetFont(scoreFont, *wxBLACK);

    wxString scoreText = wxString::Format("%06d", mScore);

    // Measure the score text size
    double scoreTextWidth, scoreTextHeight;
    gp->GetTextExtent(scoreText, &scoreTextWidth, &scoreTextHeight, nullptr, nullptr);

    // Calculate the position for the score text to be centered on the scoreboard
    double scoreTextX = x - scoreTextWidth / 2;
    double scoreTextY = y + ScoreY - scoreTextHeight / 2;

    // Draw the score text on the scoreboard
    gp->DrawText(scoreText, scoreTextX, scoreTextY);

}