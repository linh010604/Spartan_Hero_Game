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
#include "ItemImage.h"
#include "ItemMeter.h"
#include "ItemScoreboard.h"
#include "Music.h"
#include "Sound.h"
#include "ItemVisitor.h"
#include "ItemSoundBoardVisitor.h"
#include "DeclarationNoteVisitor.h"
#include "LevelLoader.h"

#include <memory>

using namespace std;

bool const BeforeTrack = true;
bool const AfterTrack = false;
///Seconds in a minute
double const SecondsPerMinute = 60;

double const StartingBeat = 4;

/**
 * Constructor
 * @param PEngine Pointer to the audio engine object
 */
Game::Game(ma_engine *PEngine) : mAudioEngine(PEngine){
}

/**
 * Retrieves the GameStateManager object.
 *
 * @return A shared pointer to the GameStateManager.
 */
std::shared_ptr<GameStateManager> Game::GetGameStateManager() {
    return mGameStateManager;
}

/**
 * Draws the game scene using the provided graphics context.
 *
 * This function draws the game represented by this instance onto the provided
 * graphics context at the specified coordinates. The content is positioned
 * relative to the specified (x, y) coordinates, with adjustments made for
 * different states of the game.
 *
 * @param graphics Shared pointer to the wxGraphicsContext object for drawing.
 * @param width The width of the drawing area.
 * @param height The height of the drawing area.
 */
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
                declaration->Draw(graphics,item->GetX(), item->GetY(),BeforeTrack);
                item->Draw(graphics, declaration,BeforeTrack);
                declaration->Draw(graphics,item->GetX(), item->GetY(),AfterTrack);
                item->Draw(graphics, declaration,AfterTrack);
                break;
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
    mDeclarationNote.clear();
    mAudio.clear();
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
    auto levelLoader = LevelLoader(this);
    levelLoader.Load(filename);

    mGameStateManager = make_shared<GameStateManager>(this);

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
    MergeSoundToNote();

}

/**
* Handle updates for animation
*
* @param elapsed The time since the last update
*/
void Game::Update(double elapsed)
{
    mTimePLaying += elapsed;
    if (mTimePLaying >= 2.0) mAbsoluteBeat += elapsed * mBeatsPerMinute/ SecondsPerMinute;
    double beatsPerSecond = mBeatsPerMinute/SecondsPerMinute;
    mTimeOnTrack = mBeatsPerMeasure/beatsPerSecond;
    mGameStateManager->UpdateMeasureAndBeat();
    GameUpdate();

    for (auto music:mMusic){
        music->Update(elapsed, mTimeOnTrack);
    }
}


/**
 * Add an item to the game
 *
 * @param item New item to add
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Add a music note to the game
 *
 * @param music New item to add
 */
void Game::AddMusic(std::shared_ptr<Music> music)
{
    mMusic.push_back(music);
}

/**
 * Add a music note to the game
 *
 * @param music New item to add
 */
void Game::AddAudio(std::shared_ptr<Sound> audio)
{
    mAudio.push_back(audio);
}

/**
 * Add a declaration to the game
 *
 * @param declaration New declaration to add
 */
void Game::AddDeclaration(std::shared_ptr<Declaration> declaration)
{
    mDeclarations.push_back(declaration);
}

/**
 * Add a declaration to the game
 *
 * @param declaration New declaration to add
 */
void Game::AddDeclarationNote(std::shared_ptr<Declaration> declaration)
{
    mDeclarationNote.push_back(declaration);
}

/**
 * Handle a key press event
 *
 * @param key The key was pressed
 */
void Game::PressKey(wxChar key)
{
    if (!mAutoPlay){
        for (auto note: mMusic){
            if (note->GetKey()->GetKey() == key){
                if(!note->PlayMannualMusic())
                    break;
            }
        }
    }
}

/**
 * Accept a visitor for the collection
 *
 * @param visitor The visitor for the collection
 */
void Game::AcceptItem(ItemVisitor *visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Merges declaration notes into music notes based on their IDs.
 *
 * This function iterates through each music note and declaration note,
 * and if their IDs match, it adds the declaration note to the music note.
 */
void Game::MergeDeclarationToNote()
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

/**
 *
 * Draws the music notes using the provided graphics context.
 *
 * @param gc Shared pointer to the wxGraphicsContext object for drawing.
 */
void Game::DrawNote(std::shared_ptr<wxGraphicsContext> gc)
{
    for (auto music : mMusic)
    {
        music->Draw(gc);
    }
}

/**
 * Updates the game state based on the current conditions.
 *
 * This function checks various conditions such as beat count, game state, and time elapsed
 * to determine the appropriate state transitions and actions to take.
 */
void Game::GameUpdate()
{
    if (mState != GameState::Closing && wxRound(mAbsoluteBeat) >= (mMeasure+1) * mBeatsPerMeasure){
        mState = GameState::Closing;
        mTimePLaying = 0;
        mAudio[0]->PlayEnd();
    }
    else if (wxRound(4-mAbsoluteBeat) < 0 && mState != GameState::Playing)
    {
        mState = GameState::Playing;
    }
    else if (mTimePLaying > 2.0 && mState == GameState::Ready)
    {
        mState = GameState::Countdown;
    }
    else if (mState == GameState::Countdown && mAbsoluteBeat >= StartingBeat && !mBackPlaying)
    {
        mAudio[0]->LoadSound(mAudioEngine);
        mAudio[0]->PlaySound();
        mBackPlaying =! mBackPlaying;
    }
}

/**
 * Merges sound objects to music notes based on their names.
 *
 * This function iterates through each music note and sound object,
 * and if their names match, it adds the sound object to the music note.
 */
void Game::MergeSoundToNote()
{
    for (auto musicNote : mMusic)
    {
        for (auto audio : mAudio)
        {
            if (audio->GetName() == musicNote->GetSound()) {
                musicNote->AddSound(audio);
            }
        }
    }
}

/**
 * Updates the autoplay mode of the game.
 *
 * @param autoplay Boolean value indicating whether autoplay mode is enabled or not.
 */
void Game::UpdateAutoPlayMode(bool autoplay)
{
    mAutoPlay = autoplay;
}

/**
 * Handles key release events in the game.
 *
 * This function is called when a key is released.
 * If autoplay mode is disabled, it checks each music note for the corresponding key release,
 * and if found, releases the note.
 *
 * @param key The key released.
 */
void Game::KeyUp(wxChar key)
{
    if (!mAutoPlay){
        for (auto note: mMusic){
            if (note->GetKey()->GetKey() == key){
                if(!note->KeyUp())
                    break;
            }
        }
    }
}

/**
 * Plays the music notes automatically if autoplay mode is enabled.
 *
 * This function is called during gameplay to play the music notes automatically.
 */
void Game::AutoplayMusic()
{
    if (mAutoPlay)
        for (auto music:mMusic){
            music->PlayAutoMusic();
        }
}
