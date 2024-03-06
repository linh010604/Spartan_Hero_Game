/**
 * @file Declaration.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATION_H
#define PROJECT1_GAMELIB_DECLARATION_H

class Game;

/**
 * Base class for any declaration in our game.
 */
class Declaration {
private:
    /// The game this declaration is contained in
    Game   *mGame;

    wxString  mId = "";  ///< Id of the declaration
    double mWidth = 0;  ///< Width of the declaration
    double mHeight = 0; ///< Length of the declaration

    /// The underlying image
    std::unique_ptr<wxImage> mDeclarationImage;

    /// The bitmap we can display for this image
    std::unique_ptr<wxBitmap> mDeclarationBitmap;

protected:
    Declaration(Game *game);
public:
    virtual ~Declaration();

    /// Default constructor (disabled)
    Declaration() = delete;

    /// Copy constructor (disabled)
    Declaration(const Declaration &) = delete;

    /// Assignment operator
    void operator=(const Declaration &) = delete;

    /**
     * The width of the item
     * @return width
     */
    double GetWidth() const { return mWidth; }

    /**
     * The height of the item
     * @return heught in pixels
     */
    double GetHeight() const { return mHeight; }

    /**
     * The Id of the item
     * @return Id
     */
    wxString GetId() const { return mId; }

    /**
     * The top width of the soundboard
     * @return top width of the soundboard
     */
     virtual double GetTopWidth() {return 0;}

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game *GetGame() { return mGame;  }

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Draw this item
     * @param gp Device context to draw on
     * @param x X location
     * @param y Y location
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y);
};

#endif //PROJECT1_GAMELIB_DECLARATION_H
