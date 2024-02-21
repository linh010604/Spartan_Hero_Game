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

/**
 * Set the directory the images are stored in
 * @param dir
 */
void Game::SetImagesDirectory(const std::wstring &dir) {
    mImagesDirectory = dir + ImagesDirectory;
}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height) {
    CalculateScaleAndOffset(width, height);
    gc->PushState();

    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);


    gc->DrawRectangle(0, 0, mVirtualWidth, mVirtualHeight);

    gc->PopState();
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
