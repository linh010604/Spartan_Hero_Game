/**
 * @file ItemScoreboard.cpp
 * @author Angelina Jolie Daoud
 * @author Naod Ghebredngl
 */

#include "pch.h"
#include "Game.h"
#include "ItemScoreboard.h"
#include "DeclarationScoreBoard.h"


const int ReadyY = -10;

ItemScoreBoard::ItemScoreBoard(Game* game)
: Item(game)
    {

    }

ItemScoreBoard::ItemScoreBoard(Game *game, std::shared_ptr<DeclarationScoreBoard> declaration)
    : Item(game), mDeclarationScoreBoard(declaration)
{

    mText = L"Get Ready!";
}

void ItemScoreBoard::SetText(const std::wstring& text)
{
    mText = text;
}

void ItemScoreBoard::Draw(wxGraphicsContext *graphics)
{
    if(graphics == nullptr) return;

    auto graphicsShared = std::shared_ptr<wxGraphicsContext>(graphics, [](wxGraphicsContext*) {});

    // Upcall Declaration::Draw to draw the scoreboard image.
    mDeclarationScoreBoard->Draw(graphicsShared, this->GetX(), this->GetY());

    // Set the font for drawing the "Get Ready" text
    wxFont font(14, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, *wxBLACK);

    // Measure the text size
    double textWidth, textHeight;
    graphics->GetTextExtent(mText, &textWidth, &textHeight, nullptr, nullptr);

    // Calculate the position for the text to be centered on the scoreboard
    double textX = this->GetX() - textWidth / 2;
    double textY = this->GetY() - textHeight / 2 + ReadyY;

    // Draw the "Get Ready" text on the scoreboard
    graphics->DrawText(mText, textX, textY);
}