/**
 * @file GameTest.cpp
 * @author Linh Nguyen
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <memory>
#include <Music.h>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

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

    ASSERT_EQ(game.GetAudioSize(), 39) << L"All audio is loaded";


}

TEST_F(GameTest, LoadLevelOne) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level1.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 7) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 14) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 262) << L"All notes in music are loaded";

    ASSERT_EQ(game.GetAudioSize(), 39) << L"All audio is loaded";

}

TEST_F(GameTest, LoadLevelTwo) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level2.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 6) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 16) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 308) << L"All notes in music are loaded";

    ASSERT_EQ(game.GetAudioSize(), 34) << L"All audio is loaded";

}

TEST_F(GameTest, LoadLevelThree) {

    // Create a game
    Game game(&mAudioEngine);

    wxString level = L"levels/level3.xml";

    game.Load(level);

    ASSERT_EQ(game.GetItemSize(), 7) << L"All items are loaded";

    ASSERT_EQ(game.GetDeclarationSize(), 17) << L"All declarations are loaded";

    ASSERT_EQ(game.GetMusicSize(), 271) << L"All notes in music are loaded";

    ASSERT_EQ(game.GetAudioSize(), 43) << L"All audio is loaded";

}

TEST_F(GameTest, Iterator)
{
    // Create a game
    Game game(&mAudioEngine);

    // Add some tiles
    auto note1 = std::make_shared<Music>(&game);
    auto note2 = std::make_shared<Music>(&game);
    auto note3 = std::make_shared<Music>(&game);

    game.AddMusic(note1);
    game.AddMusic(note2);
    game.AddMusic(note3);

    // Begin points to the first item
    auto iter1 = game.begin();

    // End points after the last item
    auto iter2 = game.end();

    ASSERT_EQ(note1, *iter1) << L"First note correct";

    ++iter1;
    ASSERT_EQ(note2, *iter1) << L"Second note correct";

    ++iter1;
    ASSERT_EQ(note3, *iter1) << L"Third note correct";

    ++iter1;
    ASSERT_FALSE(iter1 != iter2);


}