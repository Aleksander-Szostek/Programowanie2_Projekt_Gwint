#include "deck.h"

deck::deck() : kontener_kart() {}

void deck::makeDeck(QString deckFile){

    Leader = new kontener_kart;

    deck_loader DL;
    Ciag_kart = DL.load_deck(deckFile);

    //validifyDeck();

    shulfe_list();
}

void deck::validifyDeck(){

    //nie ma tutaj uwzględnione liczeni czy nie ma więcej kart niż max w talii, do zrobienia później

    FrakcjaTalii = Frakcja::Neutral;

    DeckValid = true;

    int IloscJednostek = 0;
    int IloscKartSpecjalnych = 0;
    for (int i = 0; i < Ciag_kart.size(); i++) {
        if (Ciag_kart[i]->getKategoria() == (Kategoria::Melee || Kategoria::Ranged || Kategoria::Siege))
            IloscJednostek++;
        if (Ciag_kart[i]->getLeg())
            IloscKartSpecjalnych++;
    }

    if (IloscJednostek < 15 || IloscKartSpecjalnych > 10){
        qDebug()<<"Zla ilosc kart";
        DeckValid = false;
    }


//    int indeksLidera = -1;   //wartość -1 oznacza że nie ma w talii, wartość -2 oznacza że jest więcej niż 1

    for (int i = 0; i < Ciag_kart.size(); i++) {
        if (Ciag_kart[i]->getKategoria() == Kategoria::Undefined){
            qDebug()<<"KAtegoria Undefined";
            DeckValid = false;
        }
        if (Ciag_kart[i]->getFrakcja() != Frakcja::Neutral) {
//            if (Ciag_kart[i]->getKategoria() == Kategoria::Leader){
//                if (indeksLidera == -1) {
//                    indeksLidera = i;
//                }
//                else {
//                    indeksLidera = -2;
//                    DeckValid = false;
//                }
//            }
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

    for (int baza = 0; baza < Ciag_kart.size() && DeckValid; baza++) {
        int suma = 0;

        for (int test = 0; test < Ciag_kart.size(); test++) {
            if (Ciag_kart[test]->getID() == Ciag_kart[baza]->getID())
                suma++;
        }

        if (suma > Ciag_kart[baza]->getMax()) {
            DeckValid = false;
            qDebug() << "Za dużo karty: " + Ciag_kart[baza]->getNazwa();
            break;
        }
    }
}

kontener_kart* deck::getLeader() {
    return Leader;
}
void deck::makeDeckZUI(const std::vector<karta*>& wybraneKarty) {

    Ciag_kart.clear();

    for (karta* k : wybraneKarty) {
        if (k) {
            karta* nowaKarta = new karta(*k);
            Ciag_kart.push_back(nowaKarta);
        }
    }

    validifyDeck();
}
