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


TEST_F(GameTest, LoadLevelZero) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level0.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 4) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 12) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 30) << L"All notes in music are loaded";


}

TEST_F(GameTest, LoadLevelOne) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level1.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 6) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 14) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 262) << L"All notes in music are loaded";


}

TEST_F(GameTest, LoadLevelTwo) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level2.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 6) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 16) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 308) << L"All notes in music are loaded";

}

TEST_F(GameTest, LoadLevelThree) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level3.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 4) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 12) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 262) << L"All notes in music are loaded";


}