/**
 * @file Declaration.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_DECLARATION_H
#define PROJECT1_GAMELIB_DECLARATION_H

class Game;

class Declaration {
private:
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
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game *GetGame() { return mGame;  }

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Draw this item
     * @param dc Device context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y);
};

#endif //PROJECT1_GAMELIB_DECLARATION_H
