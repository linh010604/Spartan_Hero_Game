/**
 * @file Sound.h
 * @author Roshni Kaur
 *
 * File for Sound Class
 */

#ifndef PROJECT1_GAMELIB_SOUND_H
#define PROJECT1_GAMELIB_SOUND_H

#include <string>
#include <miniaudio.h>

/**
 * Allows access to Game without creating a circular dependency.
 */
class Game;

/**
 * Class for playing sound in game.
 */
class Sound
{
private:
    /// The game this sound is contained in
    Game   *mGame;

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

    void PlaySound();

    void PlayEnd();

    void LoadSound(ma_engine* audioEngine);

    void XmlLoad(wxXmlNode *node);

    /**
     * Set audio file directory
     * @param audioFile
     */
    void SetAudioFile(wxString audioFile) {mAudioFile = audioFile;};

    /**
     * Set audio volume directory
     * @param volume
     */
    void SetVolume(double volume) {mVolume = volume;};

};

#endif //PROJECT1_GAMELIB_SOUND_H
