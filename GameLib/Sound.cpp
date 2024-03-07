/**
 * @file Sound.cpp
 * @author Roshni Kaur
 */

#include "pch.h"
#include "Sound.h"
#include <miniaudio.h>

/// Directory that contains the audio files
const std::wstring AudioDirectory = L"audio";

/**
 * Load the attributes for an audio node.
 * @param node The Xml node we are loading the audio from
 */
void Sound::XmlLoad(wxXmlNode* node)
{
    node->GetAttribute(L"name", &mName);
    node->GetAttribute(L"audio", &mAudioFile);
}

/**
 * Load the sound with its directory
 * @param audioEngine audio engine of the game
 */
void Sound::LoadSound(ma_engine* audioEngine)
{
    if(audioEngine != nullptr)
    {
        auto audioFile = AudioDirectory + L"/" + mAudioFile;
        auto result = ma_sound_init_from_file(audioEngine, wxString(audioFile), 0, NULL, NULL, &mSound);
        if (result != MA_SUCCESS)
        {
            wxString msg;
            msg.Printf(L"Unable to load audio file %s - %d", audioFile, result);
            wxMessageBox( msg, wxT("miniaudio failure"), wxICON_ERROR);
        }
        else
        {
            mLoaded = true;
            ma_sound_set_volume(&mSound, mVolume);
        }
    }
}

/**
 * Destructor
 */
Sound::~Sound()
{
    if(mLoaded)
    {
        if(ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }

        ma_sound_uninit(&mSound);
    }
}

/**
 * Play the sound
 */
void Sound::PlaySound()
{
    if(mLoaded)
    {
        //If the sound is already playing, stop it first
        if(ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }

        // Always rewind to the beginning before playing
        ma_sound_seek_to_pcm_frame(&mSound, 0);

        // And play the sound!
         ma_sound_start(&mSound);
    }
}

/**
 * Stop playing the sound
 */
void Sound::PlayEnd()
{
    if(mLoaded)
    {
        // If the sound is already playing, stop it first
        if(ma_sound_is_playing(&mSound))
        {
            ma_sound_stop(&mSound);
        }
    }
}
