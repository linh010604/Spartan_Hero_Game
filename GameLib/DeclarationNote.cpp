//
// Created by naodg on 3/6/2024.
//

#include "pch.h"
#include "Game.h"
#include "DeclarationNote.h"



using namespace std;

wstring const ImageDir = L"images/";


DeclarationNote::DeclarationNote(Game *game): Declaration(game)
{

}

/**
 * Update the location of puck in time
 * @param elapsed Elapsed time in seconds
 */
void DeclarationNote::Update(double elapsed)
{
    Declaration::Update(elapsed);
}
