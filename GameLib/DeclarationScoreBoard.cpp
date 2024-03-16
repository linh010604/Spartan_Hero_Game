/**
 * @file DeclarationScoreBoard.cpp
 * @author Linh Nguyen
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include "DeclarationScoreBoard.h"
#include "GameStateManager.h"

using namespace std;

///Image directory
wstring const ImageDir = L"images/";

/// Font size to use to display the score
const int ScoreSize = 30;

/// Font size to use to display the ready
const int ReadySize = 20;

/// Font size to use to display the beat
const int BeatsSize = 30;

/// Y location to display the score
/// relative to the vertical center of the scoreboard.
const int ScoreY = 15;


/// Y location to display "Get Ready" relative to the
/// vertical center of the scoreboard. The X value is
/// chosen that centers the text
const int ReadyY = -10;
/// Y location to display the measure and beat
/// relative to the vertical center of the scoreboard.
const int BeatY = -25;

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationScoreBoard::DeclarationScoreBoard(Game *game): Declaration(game)
{
}

/**
 * Draw the declaration scoreboard on the graphics context.
 *
 * This function draws the declaration scoreboard represented by this instance onto the provided
 * graphics context at the specified coordinates. The scoreboard includes the current score, beat,
 * and readiness state of the game. The text is positioned relative to the specified (x, y)
 * coordinates, with adjustments made for different states of the game.
 *
 * @param gp The shared pointer to the graphics context on which to draw the scoreboard
 * @param x The x-coordinate where the center of the scoreboard will be positioned
 * @param y The y-coordinate where the center of the scoreboard will be positioned
 * @param before A boolean value indicating whether to draw the scoreboard before other elements
 */
void DeclarationScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before)
{
    Declaration::Draw(gp, x, y,before);

    if(gp == nullptr) return;

    std::shared_ptr<GameStateManager> gameStateManager = this->GetGame()->GetGameStateManager();

    int score = gameStateManager->GetScore();

    auto [measure, beat] = gameStateManager->GetCurrentMeasureAndBeat();

    if (this->GetGame()->GetState() == Game::GameState::Ready)
    {
        wxFont readyFont(wxSize(0,ReadySize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(readyFont, *wxBLACK);
        double textWidth, textHeight;
        gp->GetTextExtent(L"Get Ready!", &textWidth, &textHeight);
        gp->DrawText(L"Get Ready!", x - textWidth / 2, y - textHeight / 2 + ReadyY);
    }
    else if (this->GetGame()->GetState() == Game::GameState::Countdown)
    {
        wxFont readyFont(wxSize(0,BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(readyFont, *wxBLACK);
        double textWidth, textHeight;
        wxString countText = wxString::Format("%d", wxRound(4-GetGame()->GetAbsoluteBeat()));
        gp->GetTextExtent(countText, &textWidth, &textHeight);
        gp->DrawText(countText, x - textWidth / 2, y - textHeight / 2 + BeatY);

        wxFont scoreFont(wxSize(0,BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(scoreFont, *wxBLACK);
        wxString scoreText = wxString::Format("%06d", score);
        gp->GetTextExtent(scoreText, &textWidth, &textHeight);
        gp->DrawText(scoreText, x - textWidth / 2, y - textHeight / 2 + ScoreY);
    }
    else if (this->GetGame()->GetState() == Game::GameState::Playing)
    {
        wxFont beatFont(wxSize(0,BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(beatFont, *wxBLACK);
        double textWidth, textHeight;
        wxString countText = wxString::Format("%d:%d", measure, beat);
        gp->GetTextExtent(countText, &textWidth, &textHeight);
        gp->DrawText(countText, x - textWidth / 2, y - textHeight / 2 + BeatY);

        wxFont scoreFont(wxSize(0,BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(scoreFont, *wxBLACK);
        wxString scoreText = wxString::Format("%06d", score);
        gp->GetTextExtent(scoreText, &textWidth, &textHeight);
        gp->DrawText(scoreText, x - textWidth / 2, y - textHeight / 2 + ScoreY);
    }

    // Set the font for drawing the score
    //    wxFont scoreFont(wxSize(0,ScoreSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    //    gp->SetFont(scoreFont, *wxBLACK);

    //wxString scoreText = wxString::Format("%06d", mScore);
}
