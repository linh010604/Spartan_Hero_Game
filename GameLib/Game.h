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

    //wxBitmap *mBackground;  ///< Background image to use

    ma_engine* mAudioEngine;

    /// All of the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// All of the declarations to populate our aquarium
    std::vector<std::shared_ptr<Declaration>> mDeclarations;

public:

    /// Size of the area we are going to draw on in pixels
    constexpr static double Size = 1000;

    /**
     * Get size of mItems
     * return size of mItems
     */
     size_t GetItemSize() const {return mItems.size();}

    /**
     * Get size of mDeclarations
     * return size of mDeclarations
     */
    size_t GetDeclarationSize() const {return mDeclarations.size();}

    /**
     * Game Constructor
     */
    Game(ma_engine *PEngine);

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

    void AddItem(std::shared_ptr<Item> item);

    void AddDeclaration(std::shared_ptr<Declaration> declaration);

    void XmlDeclarations(wxXmlNode *node);

    void XmlItems(wxXmlNode *node);

    ma_engine* GetAudioEngine() {return mAudioEngine;}

};

#endif //PROJECT1_GAMELIB_GAME_H
