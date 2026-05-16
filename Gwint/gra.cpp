#include "gra.h"
#include <random>
#include <QPushButton>
#include <QLayout>

gra::gra() {}
void gra::clearBoard(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza){
    /*
    for(int i =0; i< kartyPlansza.size();i++){//usuwa karte z planszy
        if(kartyPlansza[i]!=nullptr){
            plansza->removeWidget(kartyPlansza[i]);
            kartyPlansza[i]->hide();
            kartyPlansza[i]->deleteLater(); // ta funkcja zwalnia RAM w bezpiecznym momencie, aby nie zcrushwalo programu
            qDebug() << "Usunieto karte: " << kartyPlansza[i]->getCardData()->getNazwa();
        }
    }
    kartyPlansza.clear();
    //ta funkcja usuwa wszystkie karty które obecnie znajdują się na planszy(dodałem testową planszę(layout),
    //aby przetestwac czy działa, nie usuwa ona kart z ręki gracza)
    //ta funkcja jest private wiec dodalem czyszczeniePlanszy w public
    //przyciski generujesz za pomocą kalsy Card_Button, masz przykład w mainwindow.cpp jak to wygląda
    //robisz nowy przycisk, pobierzasz dane z karty, i refreshujesz aby przycisk jakos wyglądał
    // a i jeszcze tą pętlę for z tej funckcji mozna zastąpic takim zapisem, gemini mi go wypluł jak wpisałem swoj kod
    //podobno jest lepszy to można go użyć
    */
    if (!plansza) return;


    for (Card_Button* karta : kartyPlansza) {
        if (karta != nullptr) {
            plansza->removeWidget(karta);
            karta->hide();
            karta->deleteLater();
            qDebug() << "Usunieto karte: "<<karta->getCardData()->getNazwa();
        }
    }


    kartyPlansza.clear();
}


void gra::redrawBoard(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent){

    //std::vector<Card_Button*> kopia_kartyPlansza = kartyPlansza;
    clearBoard(kartyPlansza,plansza);
    for (karta* daneKarty : daneKartNaPlanszy) {
        if (daneKarty != nullptr) {
            Card_Button* nowaKarta = new Card_Button(daneKarty, parent);
            nowaKarta->refresh();
            plansza->addWidget(nowaKarta);
            kartyPlansza.push_back(nowaKarta);
            qDebug() << "Narysowano karte: "<<nowaKarta->getCardData()->getNazwa();

        }
    }

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
void gra::zagranoKarte(karta* nowaKarta, std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent){
    if(!nowaKarta){
        qDebug()<<"nie zagrano karty";
        return;
    }

    daneKartNaPlanszy.push_back(nowaKarta);//dodaje dane zagranej karty do vectora
    redrawBoard(kartyPlansza,plansza,parent);//wywołuje przeryswanie
}
void gra::przerysowaniePlanszy(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent){
    redrawBoard(kartyPlansza,plansza, parent);
}
void gra::gameClear(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza){//jest to funkcja tymczasowa która pozwala na absolutne wyczyszczenie planszy
    clearBoard(kartyPlansza,plansza);
    daneKartNaPlanszy.clear();
    qDebug()<<"Wszystko usuniete";
}
