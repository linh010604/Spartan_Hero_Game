/**
 * @file LevelLoader.cpp
 * @author Roshni Kaur
 */

#include "pch.h"
#include "LevelLoader.h"
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
#include "ItemSoundBoard.h"

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
    double beatsPerMeasure = 0;
    double beatsPerMinute = 0;
    double measure = 0;
    wxString backing = L"BACK";

    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox("Unable to load Game file");
        return;
    }

    mGame->Clear();

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
            XmlDeclarations(node);
        }
        else if (name == L"items")
        {
            auto node = child->GetChildren();
            XmlItems(node);
        }
        else if (name == L"music")
        {
            child->GetAttribute("beats-per-minute","0").ToDouble(&beatsPerMinute);
            child->GetAttribute("beats-per-measure","0").ToDouble(&beatsPerMeasure);
            child->GetAttribute("measures","0").ToDouble(&measure);
            backing = child->GetAttribute("backing","").ToStdWstring();
            auto node = child->GetChildren();
            XmlMusic(node);
        }
        else if (name == L"audio")
        {
            auto node = child->GetChildren();
            XmlAudio(node);
        }

    }

    mGame->SetVirtualWidth(virtualWidth);
    mGame->SetVirtualHeight(virtualHeight);
    mGame->SetBeatsPerMinute(beatsPerMinute);
    mGame->SetBeatsPerMeasure(beatsPerMeasure);
    mGame->SetMeasure(measure);
    mGame->SetBacking(backing);
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void LevelLoader::XmlDeclarations(wxXmlNode *node)
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
            mGame->AddDeclarationNote(declaration);
        }

        if (declaration != nullptr)
        {
            declaration->XmlLoad(node);
            mGame->AddDeclaration(declaration);
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
            mGame->AddItem(item);
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
            mGame->AddMusic(music);
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
        mGame->AddAudio(sound);
    }
}
