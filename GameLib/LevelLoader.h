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
class ItemVisitor;

/**
 * Base class for LevelLoader.
 */
class LevelLoader
{
private:
    /// The game the level will be loaded into
    Game   *mGame;

public:
    LevelLoader(Game *game);

    /// Default constructor (disabled)
    LevelLoader() = delete;

    /// Copy constructor (disabled)
    LevelLoader(const LevelLoader &) = delete;

    /// Assignment operator
    void operator=(const LevelLoader &) = delete;

    void Load(const wxString &filename);

    void AddItem(std::shared_ptr<Item> item, std::vector<std::shared_ptr<Item>> &items);

    void AddDeclaration(std::shared_ptr<Declaration> declaration,std::vector<std::shared_ptr<Declaration>> &declarations);

    void AddMusic(std::shared_ptr<Music> music, std::vector<std::shared_ptr<Music>> &passedMusic);

    void XmlDeclarations(wxXmlNode *node, std::vector<std::shared_ptr<Declaration>> &declarations,
                         std::vector<std::shared_ptr<Declaration>> &declarationNote);

    void XmlItems(wxXmlNode *node, std::vector<std::shared_ptr<Item>> &items);

    void XmlMusic(wxXmlNode *node, std::vector<std::shared_ptr<Sound>> &audio,
                  std::vector<std::shared_ptr<Music>> &passedMusic);

    void XmlAudio(wxXmlNode *node, std::vector<std::shared_ptr<Sound>> &audio);

    void AcceptItem(ItemVisitor* visitor, std::vector<std::shared_ptr<Item>> &items);

    void MergeDeclarationToNote(std::vector<std::shared_ptr<Music>> &music,
                                std::vector<std::shared_ptr<Declaration>> &declarationNote);

    void MergeSoundToNote(std::vector<std::shared_ptr<Music>> &music, std::vector<std::shared_ptr<Sound>> &audio);

};

#endif //PROJECT1_GAMELIB_LEVELLOADER_H
