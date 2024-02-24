/**
 * @file Game.h
 * @author Angelina Jolie Daoud
 *
 *
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

    //wxBitmap *mBackground;  ///< Background image to use

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

public:
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

    /**
    * Calculate the scaling factor and offset for rendering based on the current window size.
    *
    * @param width The current width of the window.
    * @param height The current height of the window.
    */
    void CalculateScaleAndOffset(int width, int height);

    /**
    * Draw the game's graphics onto the window.
    *
    * @param gc A shared pointer to a wxGraphicsContext object used for drawing.
    * @param width The current width of the window.
    * @param height The current height of the window.
     */
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);


    /**
    * Handle mouse click events within the game window.
    *
    * @param x The x-coordinate of the mouse click within the window.
    * @param y The y-coordinate of the mouse click within the window.
    */
    void OnLeftDown(int x, int y);

    /**
    * Draw the game's graphics onto the window using a device context.
    *
    * @param dc Pointer to a wxDC object used for drawing, representing the device context to draw on.
    */
    void OnDraw(wxDC* dc);

    void Load(const wxString &filename);

    void Clear();

    static void XmlDeclaration(wxXmlNode *node);

};

#endif //PROJECT1_GAMELIB_GAME_H

