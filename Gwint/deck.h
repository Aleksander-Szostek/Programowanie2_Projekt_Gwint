#ifndef DECK_H
#define DECK_H
#include "kontener_kart.h"

class deck : public kontener_kart {

public:
    deck();

    void makeDeck(QString deckFile);

private:

    void unvalidifyDeck();

    karta* Leader = nullptr;

    Frakcja FrakcjaTalii = Frakcja::Neutral;

    bool DeckValid = false;
};

#endif // DECK_H
