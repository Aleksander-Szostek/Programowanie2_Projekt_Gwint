#include "deck.h"
#include "deck_loader.h"

deck::deck() : kontener_kart() {}

void deck::makeDeck(QString deckFile){

    deck_loader DL;
    Ciag_kart = DL.load_deck(deckFile);

    //validifyDeck();

    shulfe_list();
}

void deck::validifyDeck(){

    //nie ma tutaj uwzględnione liczeni czy nie ma więcej kart niż max w talii, do zrobienia później

    FrakcjaTalii = Frakcja::Neutral;

    DeckValid = true;

    int indeksLidera = -1;   //wartość -1 oznacza że nie ma w talii, wartość -2 oznacza że jest więcej niż 1

    for (int i = 0; i < Ciag_kart.size(); i++) {
        if (Ciag_kart[i]->getKategoria() == Kategoria::Undefined)
            DeckValid = false;
        if (Ciag_kart[i]->getFrakcja() != Frakcja::Neutral) {
            if (Ciag_kart[i]->getKategoria() == Kategoria::Leader){
                if (indeksLidera == -1) {
                    indeksLidera = i;
                }
                else {
                    indeksLidera = -2;
                    DeckValid = false;
                }
            }
            if (FrakcjaTalii == Frakcja::Neutral)
                FrakcjaTalii = Ciag_kart[i]->getFrakcja();
            else if (FrakcjaTalii != Ciag_kart[i]->getFrakcja()) {
                DeckValid = false;
                FrakcjaTalii = Frakcja::Neutral;
                karta *returnVal = new karta;
                returnVal->setName("Error: multiple factions in one deck");
                add_card_to(returnVal, 0);
                break;
            }
        }
    }

    if (indeksLidera >= 0) {
        move_card(indeksLidera, Leader);
    }
    else if(indeksLidera == -1) {
        karta *returnVal = new karta;
        returnVal->setName("Error: no leader in deck");
        add_card_to(returnVal, 0);
    }
    else if(indeksLidera == -2) {
        karta *returnVal = new karta;
        returnVal->setName("Error: multiple leaders in deck");
        add_card_to(returnVal, 0);
    }
    else {
        karta *returnVal = new karta;
        returnVal->setName("Error: unknown leader in deck validity error");
        add_card_to(returnVal, 0);
    }



//    Ciag_kart.clear();
//
//    karta *returnVal = new karta;
//
//    returnVal->setName("Error: invalid deck");
//
//    Ciag_kart.push_back(returnVal);
//
//    karta* Leader = nullptr;
//
//    FrakcjaTalii = Frakcja::Neutral;
//
//    DeckValid = false;
}