/**
 * @file Game.h
 * @author Angelina Jolie Daoud
 *
 *
 */

#ifndef PROJECT1_GAMELIB_GAME_H
#define PROJECT1_GAMELIB_GAME_H

#include <wx/graphics.h>


class Game
{
private:
    /// Virtual playing area size
    int mVirtualWidth;
    int mVirtualHeight;

    /// Scaling factor and offsets for drawing
    double mScale;
    double mXOffset, mYOffset;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

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

    void SetImagesDirectory(const std::wstring &dir);

    // Calculate scaling and offset based on the window size
    void CalculateScaleAndOffset(int width, int height);

    // Function to draw the game
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    // Function to handle mouse click within the game
    void OnLeftDown(int x, int y);

};

#endif //PROJECT1_GAMELIB_GAME_H
