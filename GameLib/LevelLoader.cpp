/**
 * @file LevelLoader.cpp
 * @author Roshni Kaur
 */

#include "pch.h"
#include "LevelLoader.h"
#include "ItemSoundBoardVisitor.h"
#include "DeclarationNoteVisitor.h"
#include "Music.h"
#include "Sound.h"
#include "DeclarationImage.h"
#include "DeclarationMeter.h"
#include "DeclarationSoundBoard.h"
#include "DeclarationScoreBoard.h"
#include "DeclarationNote.h"
#include "ItemImage.h"
#include "ItemMeter.h"
#include "ItemScoreboard.h"

using namespace std;

/**
 * Constructor
 * @param game The game this item is a member of
 */
LevelLoader::LevelLoader(Game *game) : mGame(game)
{
}

/**
 * Clear the game data.
 *
 * Deletes all known items in the game level.
 */
void LevelLoader::Clear()
{
    mItems.clear();
    mDeclarations.clear();
    mMusic.clear();
    mDeclarationNote.clear();
    mAudio.clear();
}

void LevelLoader::Load(const wxString &filename)
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
            child->GetAttribute("beats-per-minute","0").ToDouble(&mBeatsPerMinute);
            child->GetAttribute("beats-per-measure","0").ToDouble(&mBeatsPerMeasure);
            child->GetAttribute("measures","0").ToDouble(&mMeasure);
            mBacking = child->GetAttribute("backing","").ToStdWstring();
            auto node = child->GetChildren();
            XmlMusic(node);
        }
        else if (name == L"audio")
        {
            auto node = child->GetChildren();
            XmlAudio(node);
        }

    }

    for (auto declaration: mDeclarationNote)
    {
        DeclarationNoteVisitor declarationVisitor;
        declaration->Accept(&declarationVisitor);
        int track = declarationVisitor.GetTrack();

        ItemSoundBoardVisitor visitor(track);
        AcceptItem(&visitor);
        std::shared_ptr<ItemKey> key = visitor.GetKey();
        for (auto note: mMusic){
            if (declaration->GetId() == note->GetId()){
                note->AddKey(key);
            }
        }
    }
    MergeDeclarationToNote();
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void LevelLoader::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Add a music note to the game
 * @param music New item to add
 */
void LevelLoader::AddMusic(std::shared_ptr<Music> music)
{
    mMusic.push_back(music);
}

/**
 * Add a declaration to the game
 * @param declaration New declaration to add
 */
void LevelLoader::AddDeclaration(std::shared_ptr<Declaration> declaration)
{
    mDeclarations.push_back(declaration);
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void LevelLoader::XmlDeclarations(wxXmlNode *node)
{
    // A pointer for the item we are loading

    // auto child = node->GetChildren();
    for ( *node ; node; node=node->GetNext())
    {
        shared_ptr<Declaration> declaration;
        auto name = node->GetName();
        if(name == L"image")
        {
            declaration = make_shared<DeclarationImage>(mGame);
        }
        else if(name == L"meter")
        {
            declaration = make_shared<DeclarationMeter>(mGame);
        }
        else if(name == L"sound-board")
        {
            declaration = make_shared<DeclarationSoundBoard>(mGame);
        }
        else if(name == L"score-board")
        {
            declaration = make_shared<DeclarationScoreBoard>(mGame);
        }

        else if(name == L"note")
        {
            declaration = make_shared<DeclarationNote>(mGame);
            mDeclarationNote.push_back(declaration);
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
void LevelLoader::XmlItems(wxXmlNode *node)
{
    // A pointer for the item we are loading

    // auto child = node->GetChildren();
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Item> item;
        auto name = node->GetName();
        if(name == L"image")
        {
            item = make_shared<ItemImage>(mGame);
        }
        else if(name == L"meter")
        {
            item = make_shared<ItemMeter>(mGame);
        }
        else if(name == L"sound-board")
        {
            item = make_shared<ItemSoundboard>(mGame);
        }
        else if(name == L"score-board")
        {
            item = make_shared<ItemScoreboard>(mGame);
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
void LevelLoader::XmlMusic(wxXmlNode *node)
{
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Music> music = make_shared<Music>(mGame);
        music->XmlLoad(node);
        AddMusic(music);
    }
}

/**
 * Handle a node of type audio.
 * @param node XML node
 */
void LevelLoader::XmlAudio(wxXmlNode *node)
{
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Sound> sound = make_shared<Sound>(mGame);
        sound->XmlLoad(node);
        mAudio.push_back(sound);
    }
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void LevelLoader::AcceptItem(ItemVisitor *visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

void LevelLoader::MergeDeclarationToNote()
{
    for (auto musicNote : mMusic)
    {
        for (auto declarationNote : mDeclarationNote)
        {
            if (declarationNote->GetId() == musicNote->GetId()) {
                musicNote->AddDeclaration(declarationNote);
            }
        }
    }
}