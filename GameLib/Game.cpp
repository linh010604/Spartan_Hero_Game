/**
 * @file Game.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include <memory>

using namespace std;

/// Directory containing the project images
/// relative to the resources directory.
const std::wstring ImagesDirectory = L"/images";

Game::Game() : mVirtualWidth(1304), mVirtualHeight(900), mScale(1), mXOffset(0), mYOffset(0) {
    // Load the background image into the wxBitmap member variable

    mBackgroundBitmap = wxBitmap(L"images/background1.png", wxBITMAP_TYPE_ANY);

}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height) {
    // Width of virtual pixels
    int virtualWidth = 1304;
    // Height of virtual pixels
    int virtualHeight = 900;

    // Creates Scale for X values
    auto scaleX = double(width) / double(virtualWidth);
    // Creates Scale for Y values
    auto scaleY = double(height) / double(virtualHeight);
    // Gets minimum of Scales for X and Y
    mScale = std::min(scaleX, scaleY);

    // Creates offset for X
    mXOffset = (width - virtualWidth * mScale) / 2.0;
    // Creates offset for Y
    mYOffset = (height - virtualHeight * mScale) > 0 ? (height - virtualHeight * mScale) / 2.0 : 0;

    // Saves current state of graphics
    graphics->PushState();
    // Translates the coordinates system using offsets
    graphics->Translate(mXOffset, mYOffset);
    // Scales coordinate system
    graphics->Scale(mScale, mScale);

    // Check if the background image is loaded correctly and draw it
    if (mBackgroundBitmap.IsOk()) {
        wxGraphicsBitmap gb = graphics->CreateBitmap(mBackgroundBitmap);
        graphics->DrawBitmap(gb, 0, 0, virtualWidth, virtualHeight);
    } else {

        wxBrush background(*wxRED);
        graphics->SetBrush(background);
        graphics->DrawRectangle(0, 0, virtualWidth, virtualHeight);
    }

    // Restores state of graphics
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
 *
 */
void Game::SetImagesDirectory(const std::wstring &dir) {
    mImagesDirectory = dir + ImagesDirectory;
}

/**
 * Load the game level from a .level XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox("Unable to load Game file");
        return;
    }

    Clear();
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"item")
        {
            XmlItem(child);
        }
    }
}

/**
 * Clear the game data.
 *
 * Deletes all known items in the game level.
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItem(wxXmlNode *node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    //if (type == L"")
    //{
    //    item = make_shared<>(this);
    //}
}