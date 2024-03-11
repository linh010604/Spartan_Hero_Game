/**
 * @file LevelLoader.h
 * @author Roshni Kaur
 *
 * File for LevelLoader class.
 */

#ifndef PROJECT1_GAMELIB_LEVELLOADER_H
#define PROJECT1_GAMELIB_LEVELLOADER_H

#include "miniaudio.h"

// Forward references
class Game;
class Item;
class Declaration;
class Music;
class Sound;
class ItemVisitor;

/**
 * Base class for LevelLoader.
 */
class LevelLoader
{
private:
    /// The game the level will be loaded into
    Game   *mGame;

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
    double mBeatsPerMeasure = 0;

    /// beats per minutes in this level
    double mBeatsPerMinute = 0;

    /// Current beat (absolute) in song
    double mAbsoluteBeat = 0;

    /// Total measure in this level
    double mMeasure = 0;

    /// backing music in this level
    wxString mBacking = L"BACK";

    /// how long since this lv start
    double mTimePlaying = 0;

public:
    LevelLoader(Game *game);

    /// Default constructor (disabled)
    LevelLoader() = delete;

    /// Copy constructor (disabled)
    LevelLoader(const LevelLoader &) = delete;

    /// Assignment operator
    void operator=(const LevelLoader &) = delete;

    void Load(const wxString &filename);

    void Clear();

    void AddItem(std::shared_ptr<Item> item);

    void AddDeclaration(std::shared_ptr<Declaration> declaration);

    void AddMusic(std::shared_ptr<Music> music);

    void XmlDeclarations(wxXmlNode *node);

    void XmlItems(wxXmlNode *node);

    void XmlMusic(wxXmlNode *node);

    void XmlAudio(wxXmlNode *node);

    void AcceptItem(ItemVisitor* visitor);

    void MergeDeclarationToNote();

    double GetVirtualWidth() const { return mVirtualWidth; }
    double GetVirtualHeight() const { return mVirtualHeight; }
    double GetScale() const { return mScale; }
    double GetXOffset() const { return mXOffset; }
    double GetYOffset() const { return mYOffset; }
    std::wstring GetImagesDirectory() const { return mImagesDirectory; }
    ma_engine* GetAudioEngine() const { return mAudioEngine; }
    double GetBeatsPerMeasure() const { return mBeatsPerMeasure; }
    double GetBeatsPerMinute() const { return mBeatsPerMinute; }
    double GetAbsoluteBeat() const { return mAbsoluteBeat; }
    double GetMeasure() const { return mMeasure; }
    wxString GetBacking() const { return mBacking; }
    double GetTimePlaying() const { return mTimePlaying; }
    const std::vector<std::shared_ptr<Item>>& GetItems() const { return mItems; }
    const std::vector<std::shared_ptr<Declaration>>& GetDeclarations() const { return mDeclarations; }
    const std::vector<std::shared_ptr<Declaration>>& GetDeclarationNote() const { return mDeclarationNote; }
    const std::vector<std::shared_ptr<Music>>& GetMusic() const { return mMusic; }
    const std::vector<std::shared_ptr<Sound>>& GetAudio() const { return mAudio; }

};

#endif //PROJECT1_GAMELIB_LEVELLOADER_H
