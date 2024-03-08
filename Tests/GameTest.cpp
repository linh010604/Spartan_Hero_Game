/**
 * @file AquariumTest.cpp
 * @author thaol
 */

#include <pch.h>
#include "gtest/gtest.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include <Game.h>

using namespace std;

class GameTest : public ::testing::Test
{
protected:
    ma_engine mAudioEngine;

};

TEST_F(GameTest, Construct){
    Game game(&mAudioEngine);
}


TEST_F(GameTest, Load) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level0.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 4) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 12) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 30) << L"All notes in music are loaded";


}


