/**
 * @file Sound.h
 * @author Roshni Kaur
 *
 * File for the Sound Class
 */

#ifndef PROJECT1_GAMELIB_SOUND_H
#define PROJECT1_GAMELIB_SOUND_H

#include <string>
#include <miniaudio.h>

// Forward Reference
class Game;

/**
 * Class for playing the sound in game.
 */
class Sound
{
private:
    /// The game this sound is contained in
    Game *mGame;

    /// Name of the sound
    wxString mName;

    /// The audio file to load
    wxString mAudioFile;

    /// long sound or not
    bool mLong = false;

    /// volume of the sound
    double mVolume = 1.0;

    /// The miniaudio sound
    ma_sound mSound;

    /// Has the sound been loaded?
    bool mLoaded = false;

public:

    ~Sound();

    /// Default constructor (disabled)
    Sound() = delete;

    /// Copy constructor (disabled)
    Sound(const Sound &) = delete;

    /// Assignment operator
    void operator=(const Sound &) = delete;

    Sound(Game *game);

    /**
     * CHeck if the sound is long or not
     * @return mLong of the sound
     */
    bool GetLong() { return mLong; }

    void PlaySound();

    void PlayEnd();

    void LoadSound(ma_engine *audioEngine);

    void XmlLoad(wxXmlNode *node);

    /**
     * Get name of the sound
     * @return mName the name of the sound
     */
    wxString GetName() { return mName; }

};

#endif //PROJECT1_GAMELIB_SOUND_H
