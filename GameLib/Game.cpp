/**
 * @file Game.cpp
 * @author Angelina Jolie Daoud
 */

#include "pch.h"
#include "Game.h"
#include "Declaration.h"
#include "DeclarationImage.h"
#include "DeclarationMeter.h"
#include "DeclarationSoundBoard.h"
#include "DeclarationScoreBoard.h"
#include "DeclarationNote.h"
#include "ItemImage.h"
#include "ItemMeter.h"
#include "ItemSoundboard.h"
#include "ItemScoreboard.h"
#include "Music.h"
#include "Sound.h"
#include "ItemVisitor.h"
#include <memory>

using namespace std;

/// Directory containing the project images
/// relative to the resources directory.
const std::wstring ImagesDirectory = L"/images";

Game::Game(ma_engine *PEngine) : mAudioEngine(PEngine), mVirtualWidth(1304), mVirtualHeight(900), mScale(1), mXOffset(0), mYOffset(0) {
}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height) {
    // Width of virtual pixels
    int virtualWidth = mVirtualWidth;
    // Height of virtual pixels
    int virtualHeight = mVirtualHeight;

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

    wxImage puckImage(L"images/puck-a.png", wxBITMAP_TYPE_ANY); // Adjust path as necessary
    if (puckImage.IsOk()) {
        wxBitmap puckBitmap(puckImage);
        double puckX = 3000; // Example X position
        double puckY = 3000; // Example Y position
        graphics->DrawBitmap(puckBitmap, puckX, puckY, puckBitmap.GetWidth(), puckBitmap.GetHeight());
    }

    // Saves current state of graphics
    graphics->PushState();
    // Translates the coordinates system using offsets
    graphics->Translate(mXOffset, mYOffset);
    // Scales coordinate system
    graphics->Scale(mScale, mScale);

    for (auto item : mItems)
    {
        for (auto declaration : mDeclarations)
        {
            if (item->GetId() == declaration->GetId()){
                declaration->Draw(graphics,item->GetX(), item->GetY());
                item->Draw(graphics, declaration);
            }
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
    mDeclarations.clear();
    mMusic.clear();
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

    auto sizeString = root->GetAttribute("size","0,0");
    sizeString.BeforeFirst(',').ToDouble(&mVirtualWidth);
    sizeString.AfterFirst(',').ToDouble(&mVirtualHeight);

    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"declarations")
        {
            auto node = child->GetChildren();
            XmlDeclarations(node);
        }
        else if (name == L"items")
        {
            auto node = child->GetChildren();
            XmlItems(node);
        }
        else if (name == L"music")
        {
            auto node = child->GetChildren();
            XmlMusic(node);
        }
        else if (name == L"audio")
        {
            auto node = child->GetChildren();
            XmlAudio(node);
        }

    }
}

/**  Handle updates for animation
* @param elapsed The time since the last update
*/
void Game::Update(double elapsed)
{
    for (auto declaration : mDeclarations)
    {
        declaration->Update(elapsed);
    }
}


/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Add a declaration to the game
 * @param declaration New declaration to add
 */
void Game::AddDeclaration(std::shared_ptr<Declaration> declaration)
{
    mDeclarations.push_back(declaration);
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlDeclarations(wxXmlNode *node)
{
    // A pointer for the item we are loading

    // auto child = node->GetChildren();
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Declaration> declaration;
        auto name = node->GetName();
        if(name == L"image")
        {
            declaration = make_shared<DeclarationImage>(this);
        }
        else if(name == L"meter")
        {
            declaration = make_shared<DeclarationMeter>(this);
        }
        else if(name == L"sound-board")
        {
            declaration = make_shared<DeclarationSoundBoard>(this);
        }
        else if(name == L"score-board")
        {
            declaration = make_shared<DeclarationScoreBoard>(this);
        }

        else if(name == L"note")
        {
            declaration = make_shared<DeclarationNote>(this);
        }

        if (declaration != nullptr)
        {
            declaration->XmlLoad(node);
            AddDeclaration(declaration);
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItems(wxXmlNode *node)
{
    // A pointer for the item we are loading

    // auto child = node->GetChildren();
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Item> item;
        auto name = node->GetName();
        if(name == L"image")
        {
            int a = 1;
            item = make_shared<ItemImage>(this);
        }
        else if(name == L"meter")
        {
            item = make_shared<ItemMeter>(this);
        }
        else if(name == L"sound-board")
        {
            item = make_shared<ItemSoundboard>(this);
        }
        else if(name == L"score-board")
        {
            item = make_shared<ItemScoreboard>(this);
        }

        if (item != nullptr)
        {
            item->XmlLoad(node);
            AddItem(item);
        }
    }
}

/**
 * Handle a node of type music.
 * @param node XML node
 */
void Game::XmlMusic(wxXmlNode *node)
{
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Music> music = make_shared<Music>(this);
        music->XmlLoad(node);
        mMusic.push_back(music);
    }
}

/**
 * Handle a node of type audio.
 * @param node XML node
 */
void Game::XmlAudio(wxXmlNode *node)
{
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Sound> sound = make_shared<Sound>(this);
        sound->XmlLoad(node);
        mAudio.push_back(sound);
    }
}

/**
 * Handle a key press event
 * @param key The key was pressed
 */
void Game::PressKey(wxChar key)
{

}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor *visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}
