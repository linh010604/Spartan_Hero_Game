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

/// Font size to use to display the ready
const int ReadySize = 20;

/// Font size to use to display the beat
const int BeatsSize = 30;

/// Y location to display the score
/// relative to the vertical center of the scoreboard.
const int ScoreY = 15;

const int ReadyY = -10;

const int BeatY = -25;

/**
 * Constructor
 * @param game Game this declaration is a member of
 */
DeclarationScoreBoard::DeclarationScoreBoard(Game *game) : Declaration(game)
{
}

void DeclarationScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before)
{
    Declaration::Draw(gp, x, y, before);

    if(gp == nullptr)
        return;

    std::shared_ptr<GameStateManager> gameStateManager = this->GetGame()->GetGameStateManager();

    int score = gameStateManager->GetScore();

    auto [measure, beat] = gameStateManager->GetCurrentMeasureAndBeat();

    if(this->GetGame()->GetState() == Game::GameState::Ready)
    {
        wxFont readyFont(wxSize(0, ReadySize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(readyFont, *wxBLACK);
        double textWidth, textHeight;
        gp->GetTextExtent(L"Get Ready!", &textWidth, &textHeight);
        gp->DrawText(L"Get Ready!", x - textWidth / 2, y - textHeight / 2 + ReadyY);
    }
    else if(this->GetGame()->GetState() == Game::GameState::Countdown)
    {
        wxFont readyFont(wxSize(0, BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(readyFont, *wxBLACK);
        double textWidth, textHeight;
        wxString countText = wxString::Format("%d", wxRound(4 - GetGame()->GetAbsoluteBeat()));
        gp->GetTextExtent(countText, &textWidth, &textHeight);
        gp->DrawText(countText, x - textWidth / 2, y - textHeight / 2 + BeatY);

        wxFont scoreFont(wxSize(0, BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(scoreFont, *wxBLACK);
        wxString scoreText = wxString::Format("%06d", score);
        gp->GetTextExtent(scoreText, &textWidth, &textHeight);
        gp->DrawText(scoreText, x - textWidth / 2, y - textHeight / 2 + ScoreY);
    }
    else if(this->GetGame()->GetState() == Game::GameState::Playing
        || this->GetGame()->GetState() == Game::GameState::Closing)
    {
        wxFont beatFont(wxSize(0, BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(beatFont, *wxBLACK);
        double textWidth, textHeight;
        wxString countText = wxString::Format("%d:%d", measure, beat);
        gp->GetTextExtent(countText, &textWidth, &textHeight);
        gp->DrawText(countText, x - textWidth / 2, y - textHeight / 2 + BeatY);

        wxFont scoreFont(wxSize(0, BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(scoreFont, *wxBLACK);
        wxString scoreText = wxString::Format("%06d", score);
        gp->GetTextExtent(scoreText, &textWidth, &textHeight);
        gp->DrawText(scoreText, x - textWidth / 2, y - textHeight / 2 + ScoreY);
    }

}
