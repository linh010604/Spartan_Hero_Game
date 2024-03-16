/**
 * @file Music.h
 * @author Linh Nguyen
 *
 * File for the Music Class.
 */

#ifndef PROJECT1_GAMELIB_MUSIC_H
#define PROJECT1_GAMELIB_MUSIC_H

#include "Declaration.h"
#include "ItemKey.h"
#include "Sound.h"

/// Forward Reference
class Game;

/**
 * Base class for any music in our game.
 */
class Music
{
private:
    std::shared_ptr<Declaration> mDeclaration; ///< Shared pointer to declarations
    std::shared_ptr<ItemKey> mKey; ///< Shared pointer to item keys
    std::shared_ptr<Sound> mAudio; ///< Shared pointer to audio sounds

    /// The game this item is contained in
    Game *mGame;

    // Note location in the game
    double mX = 0;     ///< X location for the center of the note
    double mY = 0;     ///< Y location for the center of the note
    // Note red line location in the game
    double mLongX = 0;     ///< X long red line location from the center of the note
    double mLongY = 0;     ///< Y long red line location from the center of the note

    wxString mId = L"";  ///< Id of the sound
    wxString mSound = L"";  ///< Sound name of the sound
    int mMeasure = 0;///<Measure of the sound
    double mBeat = 0;///<Measure of the sound
    double mDuration = 0;///<Measure of the sound
    bool mFirstUpdate = false;///<Check if this is time for note to appear
    bool mPlayMusic = false; ///<Check if this note has been played or not
    double mBeatPlay = 0; ///< Beat which the note are played
    bool mContinueDurationLine = false; ///<check if we still need to draw red line
    bool mStopAtKey = false; ///< check if note hit the key

public:
    ~Music();

    /**
     * Get the pointer to the Level object
     * @return Pointer to Level object
     */
    Game *GetGame() { return mGame; }

    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * The Id of the item
     * @return Id
     */
    wxString GetId() const { return mId; }

    /**
     * @return beat
     */
    double GetBeat() { return mBeat; }

    /**
     * @return measure
     */
    double GetMeasure() { return mMeasure; }

    /**
     * @return sound name
     */
    wxString GetSound() { return mSound; }

    /**
     * @return key item
     */
    std::shared_ptr<ItemKey> GetKey() { return mKey; }

    /**
     * @return duration
     */
    double GetDuration() { return mDuration; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y)
    {
        mX = x;
        mY = y;
    }

    Music(Game *game);

    /// Default constructor (disabled)
    Music() = delete;

    /// Copy constructor (disabled)
    Music(const Music &) = delete;

    /// Assignment operator
    void operator=(const Music &) = delete;

    void XmlLoad(wxXmlNode *node);

    /**
     * Match the puck with the music note
     * @param declaration the puck of this music note
     */
    void AddDeclaration(const std::shared_ptr<Declaration> &declaration) { mDeclaration = declaration; }

    /**
     * Match the sound file with the music note
     * @param sound the sound file of this music note
     */
    void AddSound(const std::shared_ptr<Sound> &sound) { mAudio = sound; }

    /**
     * Match the correct key with the music note
     * @param key the key of this music note
     */
    void AddKey(const std::shared_ptr<ItemKey> &key) { mKey = key; }

    void Draw(std::shared_ptr<wxGraphicsContext> gp);

    void Update(double elapsed, double timeOnTrack);

    bool KeyUp();

    void PlayAutoMusic();

    bool PlayManualMusic();

};

#endif //PROJECT1_GAMELIB_MUSIC_H
