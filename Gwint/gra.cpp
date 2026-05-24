#include "gra.h"
#include "karta.h"
#include <QPushButton>
#include <QLayout>
#include "i_constant_valuse.h"

gra::gra() {
    gracz_1 = new player;
    gracz_2 = new player;
}

void gra::zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2){

    nr_rundy = 0;

    gracz_1->getDeck()->makeDeck(nazwa_talii_1);
    gracz_2->getDeck()->makeDeck(nazwa_talii_2);
//    gracz_1->getDeck()->validifyDeck();
//    gracz_2->getDeck()->validifyDeck();
    if (true){  //gracz_1->getDeck()->DeckValid && gracz_2->getDeck()->DeckValid) {
        int losowanie_start = rand()%2 + 1;
            if (losowanie_start == 1) {
                GameState = Tura1;
                qDebug() << "Tura 1";
            }
            else {
                GameState = Tura2;
                qDebug() << "Tura 2";
            }
    }
    else {
        qDebug() << "Invalid deck";
        koniec_gry();
    }

    dobierzKarte(1, startHand);
    dobierzKarte(2, startHand);
}

void gra::koniec_rundy(){
    GameState = KoniecRundy;

    nr_rundy ++;

    countPoints();
    //na wszelki wypadek edge caseów liczymy jeszcze raza

    int zwyciezca = 0;

    if (p1_pkt > p2_pkt) {
        p1_gamescore++;
        zwyciezca = 1;

    }
    else if (p1_pkt < p2_pkt) {
        p2_gamescore++;
        zwyciezca = 2;
    }
    else {
        p1_gamescore++;
        p2_gamescore++;
    }

    countPoints();
    //liczymy ponownie żeby ekran końca rundy wyświetlił poprawny wynik

    qDebug() << "Sprawdzanie co po końcu rundy. Wynik: " + QString::number(p1_gamescore) + "   " + QString::number(p2_gamescore);
    if (p1_gamescore == 2 || p2_gamescore == 2) {
        qDebug() << "Koniec gry";
        koniec_gry();
    }
    else {
        nakazZmianyStrony(2);

        clearPlansza();
        gracz_1->Spasuj(true);
        gracz_2->Spasuj(true);

        if (zwyciezca == 1)
            GameState = Tura1;
        else if (zwyciezca == 2)
            GameState = Tura2;
        else {
            if (rand()%2 == 1)
                GameState = Tura1;
            else
                GameState = Tura2;
        }
    }
}

void gra::koniec_gry(){
    GameState = KoniecGry;

    if (p1_gamescore == 0 && p2_gamescore == 0) {
        nakazZmianyStrony(0);
        qDebug() << "Gra nierozpoczęta ze względu na niewłaściewośc 1 z talii";
        return;
    }
    else {
        nakazZmianyStrony(2);
    }

        p1_gamescore = 0;
        p2_gamescore = 0;

        player* temp_p1 = gracz_1;
        player* temp_p2 = gracz_2;

        gracz_1 = new player;
        gracz_2 = new player;

        delete temp_p1;
        delete temp_p2;

        qDebug() << "Koniec gry";
}

void gra::graczZagrajKarte(int nr_w_rece, int nr_gracza){
    if (nr_gracza == 1 && GameState == Tura1){
        qDebug() << "Gracz 1 zagrał";
        globalCardPlayed(gracz_1->zagrajKarte(nr_w_rece), 1);
        if (!gracz_2->isPas()){
            GameState = Tura2;
            qDebug() << "Tura 2";
        }
    }

    if (nr_gracza == 2 && GameState == Tura2){
        qDebug() << "Gracz 2 zagrał";
        globalCardPlayed(gracz_2->zagrajKarte(nr_w_rece), 2);
        if (!gracz_1->isPas()){
            GameState = Tura1;
            qDebug() << "Tura 1";
        }
    }

    return;
}

void gra::globalCardPlayed(karta* karta_g, int nr_gracza){
    qDebug() << "globalCardPlayed active";
    if (karta_g != nullptr) {
        //tutaj będą robione karty pogody i szpiedzy
    }
    redrawBoard();
    return;
}

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

    qDebug() << "Przerysowywanie planszy";

    for (int i = 0; i<gracz_1->getReka()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getReka()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Hand, i, 1);
    }

    qDebug() << "Przerysowywanie reki done";

    for (int i = 0; i < gracz_1->getMelee()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getMelee()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Melee, i, 1);
    }

    qDebug() << "Przerysowywanie m1 done";

    for (int i = 0; i<gracz_1->getRanged()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getRanged()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Range, i, 1);
    }

    qDebug() << "Przerysowywanie r1 done";

    for (int i = 0; i<gracz_2->getMelee()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getMelee()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Melee, i, 2);
    }
    qDebug() << "Przerysowywanie m2 done";

    for (int i = 0; i < gracz_2->getRanged()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getRanged()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Range, i, 2);
    }

    qDebug() << "Przerysowywanie r2 done";

    for (int i = 0; i < gracz_1->getSiege()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getSiege()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Siege, i, 1);
    }

    qDebug() << "Przerysowywanie s1 done";

    for (int i = 0; i < gracz_2->getSiege()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getSiege()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Siege, i, 2);
    }

    qDebug() << "Przerysowywanie s2 done";

    countPoints();

    qDebug() << "Przerysowywanie: count points";

    emit nakazShowGS(GameState, gracz_1->isPas(), gracz_2->isPas());

    qDebug() << "Przerysowywanie liczb done";
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
    gracz_1->wyczysc();
    gracz_2->wyczysc();
    //clearBoard();
    //z redrawBoard ręka gracza nie znika(bo koorzystając z clearBoard ręka gracza znika do następnej akcji typu kliknięcie przycisku karty)
    redrawBoard();
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

void gra::wybranoKarte(RzadPlanszy lokacja, int indeks){

}

void gra::countPoints() {
    int punkty[12];

    punkty[int(Pkt::p1_M)] = gracz_1->getMelee()->getPoints(int(Pkt::p1_M));
    punkty[int(Pkt::p1_R)] = gracz_1->getRanged()->getPoints(int(Pkt::p1_R));
    punkty[int(Pkt::p1_S)] = gracz_1->getSiege()->getPoints(int(Pkt::p1_S));
    punkty[int(Pkt::p2_M)] = gracz_2->getMelee()->getPoints(int(Pkt::p2_M));
    punkty[int(Pkt::p2_R)] = gracz_2->getRanged()->getPoints(int(Pkt::p2_R));
    punkty[int(Pkt::p2_S)] = gracz_2->getSiege()->getPoints(int(Pkt::p2_S));

    p1_pkt = punkty[int(Pkt::p1_M)] + punkty[int(Pkt::p1_R)] + punkty[int(Pkt::p1_S)];
    p2_pkt = punkty[int(Pkt::p2_M)] + punkty[int(Pkt::p2_R)] + punkty[int(Pkt::p2_S)];

    punkty[int(Pkt::p1_DS)] = gracz_1->getDeck()->getDeckSize();
    punkty[int(Pkt::p2_DS)] = gracz_2->getDeck()->getDeckSize();
    punkty[int(Pkt::p1_HS)] = gracz_1->getReka()->getDeckSize();
    punkty[int(Pkt::p2_HS)] = gracz_2->getReka()->getDeckSize();

    punkty[int(Pkt::p1_GS)] = p1_gamescore;
    punkty[int(Pkt::p2_GS)] = p2_gamescore;

    nakazAktualizacjiPunkt(punkty);
}

void gra::graczPas(int nr_gr) {
    if (nr_gr == 1 && GameState == Tura1) {
        gracz_1->Spasuj();
        if (gracz_2->isPas()) {
            koniec_rundy();
        }
        else {
            GameState = Tura2;
        }
    }
    else if (nr_gr == 2 && GameState == Tura2) {
        gracz_2->Spasuj();
        if (gracz_1->isPas()) {
            koniec_rundy();
        }
        else {
            GameState = Tura1;
        }
    }

    redrawBoard();
}

void gra::clearPlansza() {
    gracz_1->wyczysc();
    gracz_2->wyczysc();
    redrawBoard();
}

StanGry gra::getGameState() {
    return GameState;
}

int gra::getNrRundy(){
    return nr_rundy;
}