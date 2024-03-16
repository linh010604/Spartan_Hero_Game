/**
 * @file Game.h
 * @author Angelina Jolie Daoud
 * @author Linh Thao Nguyen
 *
 * File for Game class
 */

#ifndef PROJECT1_GAMELIB_GAME_H
#define PROJECT1_GAMELIB_GAME_H

#include <wx/graphics.h>
#include <memory>
#include <wx/xml/xml.h>
#include <wx/dc.h>
#include "miniaudio.h"
#include "ItemVisitor.h"
#include "DeclarationVisitor.h"
#include "GameStateManager.h"

// Forward references
class Item;
class Declaration;
class Music;
class Sound;

/**
 * Class for our game
 */
class Game
{
public:
    enum class GameState {Ready, Countdown, Playing, Closing};
    std::shared_ptr<GameStateManager> GetGameStateManager();

private:
    /**
    * Represents the width of the virtual playing area.
    */
    double mVirtualWidth;
    /**
    * Represents the height of the virtual playing area.
    */
    double mVirtualHeight;

    /**
    * Represents the scaling factor of the virtual playing area.
    */
    double mScale;

    /**
    * X offset for drawing
    */
    double mXOffset;

    /**
    * Y offset for drawing
    */
    double mYOffset;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

    /// The audio engine for miniaudio
    ma_engine* mAudioEngine;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// All of the declarations to populate our game
    std::vector<std::shared_ptr<Declaration>> mDeclarations;

    std::vector<std::shared_ptr<Declaration>> mDeclarationNote;

    /// All of music to use our game
    std::vector<std::shared_ptr<Music>> mMusic;

    /// All of audio to use our game
    std::vector<std::shared_ptr<Sound>> mAudio;

    /// beats per measure in this level
    int mBeatsPerMeasure = 0;

    /// beats per minutes in this level
    double mBeatsPerMinute = 0;

    /// Current beat (absolute) in song
    double mAbsoluteBeat = 0;

    /// Total measure in this level
    double mMeasure = 0;

    /// backing music in this level
    wxString mBacking = L"BACK";

    /// how long since this lv start
    double mTimePLaying = 0;

    GameState mState = GameState::Ready;

    double mTimeOnTrack; ///< time on track

    bool mBackPlaying = false; ///< Check if the background is played or not

    bool mAutoPlay = false; ///< Autoplay mode of the game

    int mNumberOfPlayedNote = 0; ///<The number of note have been played

    int mTotalNote = 0 ;///< Total notes have been pass

    std::shared_ptr<GameStateManager> mGameStateManager;

public:

    /// Size of the area we are going to draw on in pixels
    constexpr static double Size = 1000;

    /** Iterator that iterates over the Music notes */
    class Iter
    {
    public:
        /** Constructor
         * @param game The game we are iterating over
         * @param pos Position in the collection
         */
        Iter(Game* game, int pos) : mGame(game), mPos(pos){}

        /**
         * Compare two iterators
         * @param other The other iterator we are comparing to
         * @return  true if this position is not equal to the other position
        */
        bool operator!=(const Iter& other) const
        {
            return mPos != other.mPos;
        }

        /**
         * Get value at current position
         * @return Value at mPos in the collection
         */
        std::shared_ptr<Music> operator *() const { return mGame->mMusic[mPos]; }

        /**
         * Increment the iterator
         * @return Reference to this iterator */
        const Iter& operator++()
        {
            mPos++;
            return *this;
        }

    private:
        Game* mGame;   ///< Game we are iterating over
        int mPos;       ///< Position in the collection
        ma_engine* mAudioEngine; ///< The audio engine for miniaudio
    };

    /**
     * Get an iterator for the beginning of the collection
     * @return Iter object at position 0
     */
    Iter begin() { return Iter(this, 0); }

    /**
     * Get an iterator for the end of the collection
     * @return Iter object at position past the end
     */
    Iter end() { return Iter(this, mMusic.size()); }

    /**
     * Get size of mItems
     * @return size of mItems
     */
    size_t GetItemSize() const {return mItems.size();}

    /**
     * Get size of mAudio
     * @return size of mAudio
     */
    size_t GetAudioSize() const {return mAudio.size();}

    /**
     * Get size of mMusic
     * @return size of mMausic
     */
    size_t GetMusicSize() const {return mMusic.size();}

    /**
     * Get size of mDeclarations
     * @return size of mDeclarations
     */
    size_t GetDeclarationSize() const {return mDeclarations.size();}

    int GetPlayedNote() const {return mNumberOfPlayedNote ; }

    int GetTotalNote() const {return mTotalNote ;}

    /**
     * Game Constructor
     * @param PEngine The audio engine for miniaudio
     */
    Game(ma_engine *PEngine);

    /**
     * Destructor
    */
    virtual ~Game() = default;

    /**
     * @return mVirtualWidth
     */
    double GetWidth() const {return mVirtualWidth;}

    /**
    * @return mVirtualHeight
    */
    double GetHeight() const {return mVirtualHeight;}

    /**
    * @return mBeatsPerMinute
    */
    double GetBeatsPerMinute() const {return mBeatsPerMinute;}
    /**
    * @return mBeatsPerMersure
    */
    double GetBeatsPerMersure() const {return mBeatsPerMeasure;}
    /**
    * @return current beat
    */
    double GetAbsoluteBeat() const {return mAbsoluteBeat;}
    /**
    * @return the game measure
    */
    double GetMeasure() const {return mMeasure;}

    /**
    * @return mState
    */
    GameState GetState() const {return mState;}

    /**
    * @return mAutoPLay
    */
    bool GetAutopPlayState() const {return mAutoPlay;}


    /**
    * Draw the game's graphics onto the window.
    *
    * @param gc A shared pointer to a wxGraphicsContext object used for drawing.
    * @param width The current width of the window.
    * @param height The current height of the window.
     */
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    void Load(const wxString &filename);

    void Clear();

    void AddItem(std::shared_ptr<Item> item);

    void AddDeclaration(std::shared_ptr<Declaration> declaration);

    void AddDeclarationNote(std::shared_ptr<Declaration> declaration);

    void AddMusic(std::shared_ptr<Music> music);

    void AddAudio(std::shared_ptr<Sound> audio);

    void PressKey(wxChar key);

    void KeyUp(wxChar key);

    void Update(double elapsed);

    /**
     * Setter for virtualWidth
     * @param virtualWidth
     */
    void SetVirtualWidth(double virtualWidth) {mVirtualWidth = virtualWidth;}

    /**
     * Setter for virtualHeight
     * @param virtualHeight
     */
    void SetVirtualHeight(double virtualHeight) {mVirtualHeight = virtualHeight;}

    /**
     * Setter for beatsPerMinute
     * @param beatsPerMinute
     */
    void SetBeatsPerMinute(double beatsPerMinute) {mBeatsPerMinute = beatsPerMinute;}

    /**
     * Setter for beatsPerMeasure
     * @param beatsPerMeasure
     */
    void SetBeatsPerMeasure(int beatsPerMeasure) {mBeatsPerMeasure = beatsPerMeasure;}

    /**
     * Setter for measure
     * @param measure
     */
    void SetMeasure(int measure){mMeasure = measure;}

    /**
     * Setter for backing
     * @param backing
     */
    void SetBacking(wxString backing) {mBacking = backing;}

    /**
     *
     * @return mAudioEngine
     */
    ma_engine* GetAudioEngine() {return mAudioEngine;}

    void AcceptItem(ItemVisitor* visitor);

    void MergeDeclarationToNote();

    void MergeSoundToNote();

    void DrawNote(std::shared_ptr<wxGraphicsContext> gc);

    void GameUpdate();

    void UpdateAutoPlayMode(bool autoplay);

    void UpdatePlayedNote(){mNumberOfPlayedNote+=1;}

    void UpdateTotalNote(){mTotalNote+=1;}

    void AutoplayMusic();
};

#endif //PROJECT1_GAMELIB_GAME_H

