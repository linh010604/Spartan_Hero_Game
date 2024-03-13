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

void LevelLoader::Load(const wxString &filename)
{
    double virtualHeight;
    double virtualWidth;
    std::wstring imagesDirectory;
    double beatsPerMeasure = 0;
    double beatsPerMinute = 0;
    double absoluteBeat = 0;
    double measure = 0;
    wxString backing = L"BACK";
    double timePLaying = 0;
    std::vector<std::shared_ptr<Item>> items;
    std::vector<std::shared_ptr<Declaration>> declarations;
    std::vector<std::shared_ptr<Declaration>> declarationNote;
    std::vector<std::shared_ptr<Music>> music;
    std::vector<std::shared_ptr<Sound>> audio;

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox("Unable to load Game file");
        return;
    }

    items.clear();
    declarations.clear();
    music.clear();
    declarationNote.clear();
    audio.clear();

    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //

    auto sizeString = root->GetAttribute("size","0,0");
    sizeString.BeforeFirst(',').ToDouble(&virtualWidth);
    sizeString.AfterFirst(',').ToDouble(&virtualHeight);

    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"declarations")
        {
            auto node = child->GetChildren();
            XmlDeclarations(node, declarations, declarationNote);
        }
        else if (name == L"items")
        {
            auto node = child->GetChildren();
            XmlItems(node, items);
        }
        else if (name == L"music")
        {
            child->GetAttribute("beats-per-minute","0").ToDouble(&beatsPerMinute);
            child->GetAttribute("beats-per-measure","0").ToDouble(&beatsPerMeasure);
            child->GetAttribute("measures","0").ToDouble(&measure);
            backing = child->GetAttribute("backing","").ToStdWstring();
            auto node = child->GetChildren();
            XmlMusic(node, audio, music);
        }
        else if (name == L"audio")
        {
            auto node = child->GetChildren();
            XmlAudio(node, audio);
        }

    }

    for (auto declaration: declarationNote)
    {
        DeclarationNoteVisitor declarationVisitor;
        declaration->Accept(&declarationVisitor);
        int track = declarationVisitor.GetTrack();

        ItemSoundBoardVisitor visitor(track);
        AcceptItem(&visitor, items);
        std::shared_ptr<ItemKey> key = visitor.GetKey();
        for (auto note: music){
            if (declaration->GetId() == note->GetId()){
                note->AddKey(key);
            }
        }
    }
    MergeDeclarationToNote(music, declarationNote);

    mGame->SetVirtualWidth(virtualWidth);
    mGame->SetVirtualHeight(virtualHeight);
    mGame->SetBeatsPerMinute(beatsPerMinute);
    mGame->SetBeatsPerMeasure(beatsPerMeasure);
    mGame->SetAbsoluteBeat(absoluteBeat);
    mGame->SetMeasure(measure);
    mGame->SetBacking(backing);
    mGame->SetTimePlaying(timePLaying);
    mGame->SetItems(items);
    mGame->SetDeclarations(declarations);
    mGame->SetDeclarationNote(declarationNote);
    mGame->SetAudio(audio);
    mGame->SetMusic(music);
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void LevelLoader::AddItem(std::shared_ptr<Item> item, std::vector<std::shared_ptr<Item>> &items)
{
    items.push_back(item);
}

/**
 * Add a music note to the game
 * @param music New item to add
 */
void LevelLoader::AddMusic(std::shared_ptr<Music> music, std::vector<std::shared_ptr<Music>> &passedMusic)
{
    passedMusic.push_back(music);
}

/**
 * Add a declaration to the game
 * @param declaration New declaration to add
 */
void LevelLoader::AddDeclaration(std::shared_ptr<Declaration> declaration,std::vector<std::shared_ptr<Declaration>> &declarations)
{
    declarations.push_back(declaration);
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void LevelLoader::XmlDeclarations(wxXmlNode *node, std::vector<std::shared_ptr<Declaration>> &declarations,
                                  std::vector<std::shared_ptr<Declaration>> &declarationNote)
{
    // A pointer for the declaration we are loading

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
            declarationNote.push_back(declaration);
        }

        if (declaration != nullptr)
        {
            declaration->XmlLoad(node);
            AddDeclaration(declaration,declarations);
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void LevelLoader::XmlItems(wxXmlNode *node, std::vector<std::shared_ptr<Item>> &items)
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
            AddItem(item, items);
        }
    }
}

/**
 * Handle a node of type music.
 * @param node XML node
 */
void LevelLoader::XmlMusic(wxXmlNode *node, std::vector<std::shared_ptr<Sound>> &audio,
                           std::vector<std::shared_ptr<Music>> &passedMusic)
{
    for( *node ; node; node=node->GetNext())
    {
        if (!audio.empty())
        {
            shared_ptr<Music> music = make_shared<Music>(mGame, audio.back());
            music->XmlLoad(node);
            AddMusic(music, passedMusic);
        }
    }
}

/**
 * Handle a node of type audio.
 * @param node XML node
 */
void LevelLoader::XmlAudio(wxXmlNode *node, std::vector<std::shared_ptr<Sound>> &audio)
{
    for( *node ; node; node=node->GetNext())
    {
        shared_ptr<Sound> sound = make_shared<Sound>(mGame);
        sound->XmlLoad(node);
        audio.push_back(sound);
    }
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void LevelLoader::AcceptItem(ItemVisitor *visitor, std::vector<std::shared_ptr<Item>> &items)
{
    for (auto item : items)
    {
        item->Accept(visitor);
    }
}

void LevelLoader::MergeDeclarationToNote(std::vector<std::shared_ptr<Music>> &music,
                                         std::vector<std::shared_ptr<Declaration>> &declarationNote)
{
    for (auto musicNote : music)
    {
        for (auto declarationNote : declarationNote)
        {
            if (declarationNote->GetId() == musicNote->GetId()) {
                musicNote->AddDeclaration(declarationNote);
            }
        }
    }
}
