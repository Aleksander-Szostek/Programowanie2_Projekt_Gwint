#include "gra.h"
#include <random>

gra::gra() {}

void gra::redrawBoard(){

}

void gra::zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2){
    gracz_1->getDeck()->makeDeck(nazwa_talii_1);
    gracz_2->getDeck()->makeDeck(nazwa_talii_2);
    gracz_1->getDeck()->validifyDeck();
    gracz_2->getDeck()->validifyDeck();
    if (gracz_1->getDeck()->DeckValid && gracz_2->getDeck()->DeckValid) {
        int losowanie_start = rand()%2 + 1;
            if (losowanie_start == 1)
                GameState = Tura1;
            else
                GameState = Tura2;
    }
    else
        koniec_gry();
}

void gra::koniec_rundy(){


}

void gra::koniec_gry(){

}

void gra::graczZagrajKarte(int nr_w_rece, int nr_gracza){
    if (nr_gracza == 1 && GameState == Tura1){
        globalCardPlayed(gracz_1->zagrajKarte(nr_w_rece), 1);
    }

    if (nr_gracza == 2 && GameState == Tura2){
        globalCardPlayed(gracz_2->zagrajKarte(nr_w_rece), 2);
    }

    return;
}

void gra::globalCardPlayed(karta* karta_g, int nr_gracza){
    if (karta_g != nullptr) {

    }
    return;
}