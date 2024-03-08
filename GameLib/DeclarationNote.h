//
// Created by naodg on 3/6/2024.
//

#ifndef PROJECT1_DECLARATIONNOTE_H
#define PROJECT1_DECLARATIONNOTE_H

#include "Declaration.h"
#include "Game.h"


class DeclarationNote : public Declaration{
public:
    /// Default constructor (disabled)
    DeclarationNote() = delete;

    /// Copy constructor (disabled)
    DeclarationNote(const DeclarationNote &) = delete;

    /// Assignment operator
    void operator=(const DeclarationNote &) = delete;

    DeclarationNote(Game *game);

    void Update(double elapsed) override;

};


#endif //PROJECT1_DECLARATIONNOTE_H
