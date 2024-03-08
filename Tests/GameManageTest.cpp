#include <gtest/gtest.h>
#include "GameStateManager.h"
#include "Game.h"


class GameStateManagerTest : public ::testing::Test {
protected:
    std::unique_ptr<GameStateManager> gameStateManager;
    void SetUp() override {

        gameStateManager = std::make_unique<GameStateManager>(nullptr);
    }
};

// Use TEST_F to define tests that use the GameStateManagerTest fixture
TEST_F(GameStateManagerTest, ScoreUpdate) {
    gameStateManager->UpdateScore(10);
    ASSERT_EQ(10, gameStateManager->GetScore());
    gameStateManager->UpdateScore(5);
    ASSERT_EQ(15, gameStateManager->GetScore());
}

TEST_F(GameStateManagerTest, MeasureAndBeatUpdate) {
    gameStateManager->UpdateMeasureAndBeat(5, 3);
    auto [measure, beat] = gameStateManager->GetCurrentMeasureAndBeat();
    ASSERT_EQ(5, measure);
    ASSERT_EQ(3, beat);
}

TEST_F(GameStateManagerTest, DurationBonus) {
    gameStateManager->SetDurationBonus(0.5);
    ASSERT_EQ(5, gameStateManager->GetScore());
}
