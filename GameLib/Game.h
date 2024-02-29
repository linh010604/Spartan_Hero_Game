/**
 * @file Game.h
 * @author Angelina Jolie Daoud
 *
 * File for game class
 */

#ifndef PROJECT1_GAMELIB_GAME_H
#define PROJECT1_GAMELIB_GAME_H

#include <wx/graphics.h>
#include <memory>
#include<wx/dc.h>

/**
 * Allows access to Item without creating a circular dependency.
 */
class Item;

/**
 * Class for our game
 */
class Game
{
private:
    /**
    * Represents the width of the virtual playing area.
    */
    int mVirtualWidth;
    /**
    * Represents the height of the virtual playing area.
    */
    int mVirtualHeight;

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
    wxBitmap mBackgroundBitmap; // Member variable for the background image

    std::unique_ptr<wxBitmap> mScoreboard;

    std::unique_ptr<wxBitmap> mMeterback;

    std::unique_ptr<wxBitmap> mMetercover;

    std::unique_ptr<wxBitmap> mMeterneedle;

    std::unique_ptr<wxBitmap> mSoundboard;

    std::unique_ptr<wxBitmap> mSoundboardCover;

    //wxBitmap *mBackground;  ///< Background image to use

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

public:

    /**
     * Constructor
     */
    Game();

    /**
     * Destructor
    */
    virtual ~Game() = default;

    /**
     * Get the directory the images are stored in
     * @return Images directory path
     */
    const std::wstring &GetImagesDirectory() const { return mImagesDirectory; }


    /**
    * Set the directory where game images are stored.
    *
    * @param dir The directory path where images are stored.
    */
    void SetImagesDirectory(const std::wstring &dir);

    void CalculateScaleAndOffset(int width, int height);

    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    void OnLeftDown(int x, int y);

    void Load(const wxString &filename);

    void Clear();

    static void XmlDeclaration(wxXmlNode *node);

    void XmlItem(wxXmlNode *node);


};

#endif //PROJECT1_GAMELIB_GAME_H
