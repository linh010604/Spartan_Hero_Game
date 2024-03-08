/**
 * @file Music.h
 * @author thaol
 *
 *
 */

#ifndef PROJECT1_GAMELIB_MUSIC_H
#define PROJECT1_GAMELIB_MUSIC_H

/**
 * Allows access to Game without creating a circular dependency.
 */
class Game;

/**
 * Base class for any music in our game.
 */
class Music
{
private:


    /// The game this item is contained in
    Game   *mGame;

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the note
    double  mY = 0;     ///< Y location for the center of the note

    wxString  mId = L"";  ///< Id of the sound
    wxString  mSound = L"";  ///< Sound name of the sound
    int mMeasure = 0 ;///<Measure of the sound
    int mBeat = 0 ;///<Measure of the sound
    double mDuration = 0 ;///<Measure of the sound

public:
    ~Music();
    /**
     * The X location of the item
     * @return X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * The Id of the item
     * @return Id
     */
    wxString GetId() const { return mId; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    Music(Game *game);

    /// Default constructor (disabled)
    Music() = delete;

    /// Copy constructor (disabled)
    Music(const Music &) = delete;

    /// Assignment operator
    void operator=(const Music &) = delete;

    void XmlLoad(wxXmlNode *node);


};

#endif //PROJECT1_GAMELIB_MUSIC_H
