/**
 * @file Game.h
 * @author Angelina Jolie Daoud
 * @author Linh Thao Nguyen
 *
 */

#ifndef PROJECT1_GAMELIB_GAME_H
#define PROJECT1_GAMELIB_GAME_H

#include <wx/graphics.h>
#include <memory>
#include <wx/dc.h>
#include <miniaudio.h>

/**
 * Allows access to Item without creating a circular dependency.
 */
class Item;

/**
 * Allows access to Declaration without creating a circular dependency.
 */
class Declaration;

/**
 * Allows access to Music without creating a circular dependency.
 */
class Music;

/**
 * Allows access to Audio without creating a circular dependency.
 */
class Sound;

/**
 * Class for our game
 */
class Game
{
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

    /**
    * Represents the bitmap background of the virtual playing area.
    */
    wxBitmap mBackgroundBitmap; /// Member variable for the background image

    /// The audio engine for miniaudio
    ma_engine* mAudioEngine;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// All of the declarations to populate our game
    std::vector<std::shared_ptr<Declaration>> mDeclarations;

    /// All of music to use our game
    std::vector<std::shared_ptr<Music>> mMusic;

    /// All of audio to use our game
    std::vector<std::shared_ptr<Sound>> mAudio;

public:

    /// Size of the area we are going to draw on in pixels
    constexpr static double Size = 1000;

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
     * @return size of mMusic
     */
    size_t GetMusicSize() const {return mMusic.size();}

    /**
     * Get size of mDeclarations
     * @return size of mDeclarations
     */
    size_t GetDeclarationSize() const {return mDeclarations.size();}

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

    void XmlDeclarations(wxXmlNode *node);

    void XmlItems(wxXmlNode *node);

    void XmlMusic(wxXmlNode *node);

    void XmlAudio(wxXmlNode *node);

    void Update(double elapsed);

    /**
     *
     * @return mAudioEngine
     */
    ma_engine* GetAudioEngine() {return mAudioEngine;}

};

#endif //PROJECT1_GAMELIB_GAME_H
