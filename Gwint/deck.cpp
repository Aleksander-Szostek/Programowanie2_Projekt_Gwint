#include "deck.h"
#include "deck_loader.h"

deck::deck() : kontener_kart() {}

void deck::makeDeck(QString deckFile){

    deck_loader DL;
    Ciag_kart = DL.load_deck(deckFile);

    for (int i = 0; i < Ciag_kart.size(); i++) {
        if (Ciag_kart[i]->getKategoria() == Kategoria::Undefined)
            unvalidifyDeck();
    }
}

void deck::unvalidifyDeck(){

}