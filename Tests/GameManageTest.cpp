#include <gtest/gtest.h>
#include <memory>
#include "GameStateManager.h"

class GameStateManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<GameStateManager> gameStateManager;
    void SetUp() override {
        gameStateManager = std::make_unique<GameStateManager>(nullptr);
    }
};

TEST_F(GameStateManagerTest, ScoreUpdate) {

    gameStateManager->UpdateScore(10);
    ASSERT_EQ(10, gameStateManager->GetScore());

    gameStateManager->UpdateScore(5);
    ASSERT_EQ(15, gameStateManager->GetScore());
}

TEST_F(GameStateManagerTest, DurationBonusFullDurationHeld) {
    gameStateManager->UpdateScoreboard(true, 2.0f, 2.0f);
    ASSERT_EQ(20, gameStateManager->GetScore());
}

TEST_F(GameStateManagerTest, NoDurationBonusWhenSoundNotPlayed) {
    gameStateManager->UpdateScoreboard(false, 2.0f, 2.0f);
    ASSERT_EQ(0, gameStateManager->GetScore());
}

TEST_F(GameStateManagerTest, PartialDurationBonus) {
    gameStateManager->UpdateScoreboard(true, 1.0f, 2.0f);
    ASSERT_EQ(15, gameStateManager->GetScore());
}