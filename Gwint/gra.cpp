#include "gra.h"
#include "karta.h"
#include <QPushButton>
#include <QLayout>

gra::gra() {
    gracz_1 = new player;
    gracz_2 = new player;
}
/*
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
*/

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

    dobierzKarte(1, 10);
    dobierzKarte(2, 10);
}

void gra::koniec_rundy(){


}

void gra::koniec_gry(){

}

void gra::graczZagrajKarte(int nr_w_rece, int nr_gracza){
    if (nr_gracza == 1 && GameState == Tura1){
        globalCardPlayed(gracz_1->zagrajKarte(nr_w_rece), 1);
        if (!gracz_2->isPas())
            GameState = Tura2;
    }

    if (nr_gracza == 2 && GameState == Tura2){
        globalCardPlayed(gracz_2->zagrajKarte(nr_w_rece), 2);
        if (!gracz_1->isPas())
            GameState = Tura1;
    }


    return;
}

void gra::globalCardPlayed(karta* karta_g, int nr_gracza){
    if (karta_g != nullptr) {
        //tutaj będą robione karty pogody i szpiedzy
    }
    return;
}
// void gra::zagranoKarte(karta* nowaKarta, std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent){
//     if(!nowaKarta){
//         qDebug()<<"nie zagrano karty";
//         return;
//     }

//     daneKartNaPlanszy.push_back(nowaKarta);//dodaje dane zagranej karty do vectora
//     redrawBoard(kartyPlansza,plansza,parent);//wywołuje przeryswanie
// }
/*
void gra::zagranoKarte(karta* nowaKarta,int nr_gracza){
    if(!nowaKarta){
        qDebug()<<"nie zagrano karty";
        return;
    }
    daneKartNaPlanszy.push_back(nowaKarta);
    Kategoria category = nowaKarta->getKategoria();
    RzadPlanszy docelowyRzad = P1_Melee;
    //do dodania reszta mozliwych pozycji
    if(nr_gracza==1){
        switch(category){
            case Kategoria::Melee:
                docelowyRzad=P1_Melee;
                break;

            case Kategoria::Ranged:
                docelowyRzad=P1_Range;
                break;
            case Kategoria::Siege:
                docelowyRzad = P1_Siege;
                break;
        }
    }
    if(nr_gracza==2){
        switch(category){
        case Kategoria::Melee:
            docelowyRzad=P2_Melee;
            break;

        case Kategoria::Ranged:
            docelowyRzad=P2_Range;
            break;
        case Kategoria::Siege:
            docelowyRzad = P2_Siege;
            break;
        }
    }
    emit dodanieKarty(nowaKarta,docelowyRzad);

}*/
// void gra::przerysowaniePlanszy(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent){
//     redrawBoard(kartyPlansza,plansza, parent);
// }
// void gra::gameClear(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza){//jest to funkcja tymczasowa która pozwala na absolutne wyczyszczenie planszy
//     clearBoard(kartyPlansza,plansza);
//     daneKartNaPlanszy.clear();
//     qDebug()<<"Wszystko usuniete";
// }
void gra::clearBoard() {

    emit nakazCzyszczeniaLayoutu(P1_Melee);
    emit nakazCzyszczeniaLayoutu(P1_Range);
    emit nakazCzyszczeniaLayoutu(P1_Siege);
    emit nakazCzyszczeniaLayoutu(P2_Melee);
    emit nakazCzyszczeniaLayoutu(P2_Range);
    emit nakazCzyszczeniaLayoutu(P2_Siege);
    emit nakazCzyszczeniaLayoutu(P1_Spell);
    emit nakazCzyszczeniaLayoutu(P1_Leader);
    emit nakazCzyszczeniaLayoutu(P2_Leader);
    emit nakazCzyszczeniaLayoutu(P1_Hand);
    qDebug() << "Czyszczenie wszystkiego";
}

void gra::redrawBoard() {

    clearBoard();

    for (int i = 0; i<gracz_1->getReka()->getDeckSize(); i++) {
        karta* daneKarty = nullptr; // gracz_1->getReka()->getKartaFromList(i);
        qDebug() << "Rysowanie na planszy P1";
        emit nakazRysowaniaKarty(daneKarty, P1_Hand, i);
    }

    for (int i = 0; i < gracz_1->getMelee()->getDeckSize(); i++) {
        qDebug() << "Wykonano pętle z " + QString::number(i);
        karta* daneKarty = gracz_1->getMelee()->getKartaFromList(0);
        emit nakazRysowaniaKarty(daneKarty, P1_Melee, i);
    }

    for (int i = 0; i<gracz_1->getRanged()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getRanged()->getKartaFromList(i);
        qDebug() << "Rysowanie na range P1";
        emit nakazRysowaniaKarty(daneKarty, P1_Range, i);
    }

    for (int i = 0; i<gracz_2->getMelee()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getMelee()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Melee, i);
    }

    for (int i = 0; i < gracz_2->getRanged()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getRanged()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Range, i);
    }

    for (int i = 0; i < gracz_1->getSiege()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getSiege()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Siege, i);
    }

    for (int i = 0; i < gracz_2->getSiege()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getSiege()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Siege, i);
    }

}

void gra::zagranoKarte(int indeks, int nr_gracza) {
    if(GameState == Tura1 && nr_gracza != 1) return;
    if(GameState == Tura2 && nr_gracza != 2) return;
    karta* odczyt = nullptr;
    if (nr_gracza == 1) {
        karta* odczyt = gracz_1->getReka()->getKartaFromList(indeks);
        if (odczyt == nullptr) return;
        gracz_1->zagrajKarte(indeks);
    }
    if (nr_gracza == 2) {
        karta* odczyt = gracz_2->getReka()->getKartaFromList(indeks);
        if (odczyt == nullptr) return;
        gracz_2->zagrajKarte(indeks);
    }

    redrawBoard();
}

void gra::gameClear() {
    daneKartNaPlanszy.clear();
    clearBoard();
}

void gra::dobierzKarte(int nr_gracza, int n){
    if (nr_gracza == 1) {
        qDebug() << "Gracz 1 dobiera";
        for (int i = 0 ; i < n ; i++)
        {
            gracz_1->dobierzKarte();
        }
    }
    else if (nr_gracza == 2) {
        qDebug() << "Gracz 2 dobiera";
        for (int i = 0 ; i < n ; i++)
        {
            gracz_2->dobierzKarte();
        }
    }
    redrawBoard();
}
