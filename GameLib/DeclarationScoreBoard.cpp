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
DeclarationScoreBoard::DeclarationScoreBoard(Game *game): Declaration(game)
{
}


void DeclarationScoreBoard::Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before)
{
   Declaration::Draw(gp, x, y,before);

    if(gp == nullptr) return;


//    // Set the font for drawing the "Get Ready" text
//    wxFont font(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
//    gp->SetFont(font, *wxBLACK);

    // Measure the text size
//    gp->GetTextExtent(mText, &textWidth, &textHeight, nullptr, nullptr);

    // Draw the "Get Ready" text on the scoreboard
    //gp->DrawText(mText, textX, textY);
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
        wxString scoreText = wxString::Format("%06d", 0);
        gp->GetTextExtent(scoreText, &textWidth, &textHeight);
        gp->DrawText(scoreText, x - textWidth / 2, y - textHeight / 2 + ScoreY);
    }
    else if (this->GetGame()->GetState() == Game::GameState::Playing){
        wxFont beatFont(wxSize(0,BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(beatFont, *wxBLACK);
        double textWidth, textHeight;
        int measure = wxRound(GetGame()->GetAbsoluteBeat())/GetGame()->GetBeatsPerMersure();
        int currbeat = wxRound(GetGame()->GetAbsoluteBeat()) - measure * GetGame()->GetBeatsPerMersure()+1;
        wxString countText = wxString::Format("%d:%d", measure,currbeat);
        gp->GetTextExtent(countText, &textWidth, &textHeight);
        gp->DrawText(countText, x - textWidth / 2, y - textHeight / 2 + BeatY);

        wxFont scoreFont(wxSize(0,BeatsSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        gp->SetFont(scoreFont, *wxBLACK);
        wxString scoreText = wxString::Format("%06d", 0);
        gp->GetTextExtent(scoreText, &textWidth, &textHeight);
        gp->DrawText(scoreText, x - textWidth / 2, y - textHeight / 2 + ScoreY);
    }

    // Set the font for drawing the score
//    wxFont scoreFont(wxSize(0,ScoreSize), wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
//    gp->SetFont(scoreFont, *wxBLACK);

    //wxString scoreText = wxString::Format("%06d", mScore);
}