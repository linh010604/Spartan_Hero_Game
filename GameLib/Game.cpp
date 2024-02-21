/**
 * @file Game.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"

/// Directory containing the project images
/// relative to the resources directory.
const std::wstring ImagesDirectory = L"/images";

Game::Game() : mVirtualWidth(1304), mVirtualHeight(900), mScale(1), mXOffset(0), mYOffset(0) {}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height) {
    int virtualWidth = 1304;
    int virtualHeight = 900;

    auto scaleX = double(width) / double(virtualWidth);
    auto scaleY = double(height) / double(virtualHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - virtualWidth * mScale) / 2.0;
    mYOffset = (height - virtualHeight * mScale) > 0 ? (height - virtualHeight * mScale) / 2.0 : 0;

    graphics->PushState();
    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);


    wxBrush background(*wxRED);
    graphics->SetBrush(background);
    graphics->DrawRectangle(0, 0, virtualWidth, virtualHeight);

    graphics->PopState();
}

void Game::OnLeftDown(int x, int y) {
    double virtualX = (x - mXOffset) / mScale;
    double virtualY = (y - mYOffset) / mScale;
}

void Game::CalculateScaleAndOffset(int width, int height) {
    mScale = std::min(double(width) / mVirtualWidth, double(height) / mVirtualHeight);
    mXOffset = (width - mVirtualWidth * mScale) / 2.0;
    mYOffset = (height - mVirtualHeight * mScale) / 2.0;
}

/**
 * Set the directory the images are stored in
 * @param dir
 */
void Game::SetImagesDirectory(const std::wstring &dir) {
    mImagesDirectory = dir + ImagesDirectory;
}
