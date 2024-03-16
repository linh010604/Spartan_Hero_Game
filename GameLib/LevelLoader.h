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

/**
 * Base class for LevelLoader.
 */
class LevelLoader
{
private:
    /// The game the level will be loaded into
    Game *mGame;

public:
    LevelLoader(Game *game);

    /// Default constructor (disabled)
    LevelLoader() = delete;

    /// Copy constructor (disabled)
    LevelLoader(const LevelLoader &) = delete;

    /// Assignment operator
    void operator=(const LevelLoader &) = delete;

    void Load(const wxString &filename);

    void XmlDeclarations(wxXmlNode *node);

    void XmlItems(wxXmlNode *node);

    void XmlMusic(wxXmlNode *node);

    void XmlAudio(wxXmlNode *node);

};

#endif //PROJECT1_GAMELIB_LEVELLOADER_H
