/**
 * @file DeclarationVisitor.h
 * @author Linh Nguyen
 *
 * File for the Declaration Visitor Class
 */

#ifndef PROJECT1_GAMELIB_DECLARATIONVISITOR_H
#define PROJECT1_GAMELIB_DECLARATIONVISITOR_H

// Forward references to all declarations
class DeclarationSoundBoard;
class DeclarationImage;
class DeclarationMeter;
class DeclarationScoreBoard;
class DeclarationNote;

/**
 * Declaration visitor base class
 */
class DeclarationVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    DeclarationVisitor() {}
public:
    virtual ~DeclarationVisitor() {}

    /**
     * Visit a ItemSoundboard object
     * @param soundboard Soundboard we are visiting
     */
    virtual void VisitDeclarationSoundBoard(DeclarationSoundBoard* soundboard) {}

    /**
     * Visit a ItemScoreboard object
     * @param scoreboard Soundboard we are visiting
     */
    virtual void VisitDeclarationScoreBoard(DeclarationScoreBoard* scoreboard) {}

    /**
     * Visit a ItemSoundboard object
     * @param soundboard Soundboard we are visiting
     */
    virtual void VisitDeclarationImage(DeclarationImage* image) {}

    /**
     * Visit a ItemSoundboard object
     * @param soundboard Soundboard we are visiting
     */
    virtual void VisitDeclarationMeter(DeclarationMeter* meter) {}

    /**
     * Visit a ItemSoundboard object
     * @param soundboard Soundboard we are visiting
     */
    virtual void VisitDeclarationNote(DeclarationNote* note) {}

};

#endif //PROJECT1_GAMELIB_DECLARATIONVISITOR_H
