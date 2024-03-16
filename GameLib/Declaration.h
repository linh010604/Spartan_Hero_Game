/**
 * @file Declaration.h
 * @author Linh Nguyen
 *
 * File for the declaration class
 */

#ifndef PROJECT1_GAMELIB_DECLARATION_H
#define PROJECT1_GAMELIB_DECLARATION_H

#include "DeclarationVisitor.h"

/// Forward reference
class Game;

/**
 * Base class for any declaration in our game.
 */
class Declaration
{
private:
    /// The game this declaration is contained in
    Game *mGame;

    wxString mId = "";  ///< Id of the declaration
    double mWidth = 0;  ///< Width of the declaration
    double mHeight = 0; ///< Length of the declaration
    double mScale = 1; ///< Scale of the note

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
     * @return height in pixels
     */
    double GetHeight() const { return mHeight; }

    /**
     * Set new scale of the item
     * @param scale
     */
    void SetScale(double scale) { mScale = scale; }

    /**
     * The Id of the item
     * @return Id
     */
    wxString GetId() const { return mId; }

    /**
     * The top width of the soundboard
     * @return top width of the soundboard
     */
    virtual double GetTopWidth() { return 0; }

    /**
     * Get the pointer to the Game object
     * @return Pointer to Game object
     */
    Game *GetGame() { return mGame; }

    virtual void XmlLoad(wxXmlNode *node);

    virtual void Draw(std::shared_ptr<wxGraphicsContext> gp, double x, double y, bool before);

    /**
    * Accept a visitor
     * @param visitor The visitor we accept
     */
    virtual void Accept(DeclarationVisitor *visitor) = 0;

    ///  Handle updates for animation
    /// @param elapsed The time since the last update
    virtual void Update(double elapsed) {}

};

#endif //PROJECT1_GAMELIB_DECLARATION_H
