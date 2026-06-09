#include "gra.h"
#include "bot_player.h"
#include "karta.h"
#include <QPushButton>
#include <QLayout>
#include "i_constant_valuse.h"


gra::gra() {
    gracz_1 = new bot_player; // musimy zrbic klase np gracz_player
    gracz_2 = new bot_player;
}

void gra::zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2){
    std::srand(time(NULL));
    gracz_1->getDeck()->makeDeck(nazwa_talii_1);
    qDebug()<<"talia gracza to: "<<nazwa_talii_1;
    gracz_2->getDeck()->makeDeck(nazwa_talii_2);
    qDebug()<<"talia bota to: "<<nazwa_talii_1;
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

    if (GameState == Tura2) {
        QTimer::singleShot(1000, this, &gra::tura_bota);
    }
}





void gra::koniec_rundy(){
    GameState = KoniecRundy;

    countPoints();
    //na wszelki wypadek edge caseów liczymy jeszcze raza

    int zwyciezca = 0;

    if (p1_pkt > p2_pkt) {

        p1_gamescore++;
        gracz_1->setPunktyK(p1_gamescore);
        zwyciezca = 1;

    }
    else if (p1_pkt < p2_pkt) {
        p2_gamescore++;
        gracz_2->setPunktyK(p2_gamescore);
        zwyciezca = 2;
    }
    else {
        p1_gamescore++;
        gracz_1->setPunktyK(p1_gamescore);
        p2_gamescore++;
        gracz_2->setPunktyK(p2_gamescore);
    }

    qDebug() << "Sprawdzanie co po końcu rundy. Wynik: " + QString::number(gracz_1->getPunktyK()) + "   " + QString::number(gracz_2->getPunktyK());
    if (p1_gamescore == 2 || p2_gamescore == 2) {
        koniec_gry();
    }
    //jak ja nie mam kart i bot nie ma to automatycznie konczy sie gra
    else if((p1_gamescore==1 && gracz_1->getReka()->getDeckSize()==0)&&(p2_gamescore==1 && gracz_2->getReka()->getDeckSize()==0)){
        koniec_gry();

    }
    else {
        clearPlansza();
        gracz_1->ResetPasa();
        gracz_2->ResetPasa();

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
        if (GameState == Tura2) {
            QTimer::singleShot(1000, this, &gra::tura_bota);
        }
    }


}

void gra::koniec_gry(){
    qDebug()<<"Koniec gry";
}

// void gra::graczZagrajKarte(int nr_w_rece, int nr_gracza){
//     if (nr_gracza == 1 && GameState == Tura1){
//         globalCardPlayed(gracz_1->zagrajKarte(nr_w_rece), 1);
//         if (!gracz_2->isPas()){
//             GameState = Tura2;
//         }
//     }

//     if (nr_gracza == 2 && GameState == Tura2){
//         globalCardPlayed(gracz_2->zagrajKarte(nr_w_rece), 2);
//         if (!gracz_1->isPas()){
//             GameState = Tura1;
//         }
//     }

//     return;
// }
void gra::graczZagrajKarte(int nr_w_rece, int nr_gracza){

    if (nr_gracza == 1 && GameState == Tura1){

        globalCardPlayed(gracz_1->zagrajKarte(nr_w_rece), 1);

        redrawBoard();

        if (!gracz_2->isPas()){
            GameState = Tura2;
            QTimer::singleShot(1000, this, &gra::tura_bota);
        }
    }

    else if (nr_gracza == 2 && GameState == Tura2){

        globalCardPlayed(gracz_2->zagrajKarte(nr_w_rece), 2);

        redrawBoard();

        if (!gracz_1->isPas()){
            GameState = Tura1;
        }
        else {
            QTimer::singleShot(1000, this, &gra::tura_bota);
        }
    }
    if(gracz_1->getReka()->getDeckSize()==0){
        gracz_1->Pasuj();
        qDebug()<<"Gracz ma tyle kart: "<<gracz_1->getReka()->getDeckSize();
        if(gracz_2->isPas()){
            koniec_rundy();
        }
    }


}
void gra::globalCardPlayed(karta* karta_g, int nr_gracza){
    if (karta_g != nullptr) {
        //tutaj będą robione karty pogody i szpiedzy
    }
    //redrawBoard();
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

    for (int i = 0; i < gracz_1->getMelee()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getMelee()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Melee, i, 1);
    }

    for (int i = 0; i<gracz_1->getRanged()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getRanged()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Range, i, 1);
    }

    for (int i = 0; i<gracz_2->getMelee()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getMelee()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Melee, i, 2);
    }

    for (int i = 0; i < gracz_2->getRanged()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getRanged()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Range, i, 2);
    }

    for (int i = 0; i < gracz_1->getSiege()->getDeckSize(); i++) {
        karta* daneKarty = gracz_1->getSiege()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P1_Siege, i, 1);
    }

    for (int i = 0; i < gracz_2->getSiege()->getDeckSize(); i++) {
        karta* daneKarty = gracz_2->getSiege()->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, P2_Siege, i, 2);
    }

    countPoints();
}

// void gra::zagranoKarte(int indeks, int nr_gracza) {
//     if(GameState == Tura1 && nr_gracza != 1) return;
//     if(GameState == Tura2 && nr_gracza != 2) return;
//     karta* odczyt = nullptr;
//     if (nr_gracza == 1) {
//         karta* odczyt = gracz_1->getReka()->getKartaFromList(indeks);
//         if (odczyt == nullptr) return;
//         gracz_1->zagrajKarte(indeks);
//     }
//     if (nr_gracza == 2) {
//         karta* odczyt = gracz_2->getReka()->getKartaFromList(indeks);
//         if (odczyt == nullptr) return;
//         gracz_2->zagrajKarte(indeks);
//     }

//     redrawBoard();
// }

// void gra::zagranoKarte(int indeks, int nr_gracza){
//     if (GameState == Tura1 && nr_gracza != 1){
//         return;
//     }
//     if (GameState == Tura2 && nr_gracza != 2){
//         return;
//     }
//     karta* zagranaKarta = nullptr;

//     if(nr_gracza==1){
//         zagranaKarta= gracz_1->zagrajKarte(indeks);
//     }
//     else if(nr_gracza==2){
//         zagranaKarta = gracz_2->zagrajKarte(indeks);
//     }

//     if(nr_gracza==1){
//         if(!gracz_2->isPas()){
//             GameState = Tura2;
//             qDebug()<<"Teraz tura bota";
//             QTimer::singleShot(1000, this, &gra::tura_bota);
//             redrawBoard();
//         }
//         else{
//             qDebug()<<"Gracz spaswal, bot gra dalej";
//             redrawBoard();
//         }
//     }
//     else if(nr_gracza==2){
//         if(!gracz_1->isPas()){
//             GameState = Tura1;
//             qDebug()<<"Tura gracza";
//             redrawBoard();
//         }
//         else{
//             qDebug()<<"Gracz spaswal, bot gra dalej";
//             QTimer::singleShot(1000, this, &gra::tura_bota);
//             redrawBoard();
//         }
//     }
//     if(gracz_1->getReka()->getDeckSize()==0){
//         gracz_1->Spasuj();
//     }
// }

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


void gra::tura_bota() {

    if (GameState != Tura2){
        return;
    }

    decyzjaRuchu decyzja = gracz_2->podjecieDecyzji(gracz_1);

    if (decyzja.pasuje) {

        gracz_2->Pasuj();

        qDebug() << "Bot spasował";

        if (gracz_1->isPas()) {
            koniec_rundy();
        }
        else {
            GameState = Tura1;
        }

        redrawBoard();
        return;
    }

    graczZagrajKarte(decyzja.nr_karty, 2);
}
void gra::wybranoKarte(RzadPlanszy lokacja, int indeks){

}

void gra::countPoints() {
    int punkty[12];

    punkty[0] = gracz_1->getMelee()->getPoints(0);
    punkty[1] = gracz_1->getRanged()->getPoints(0);
    punkty[2] = gracz_1->getSiege()->getPoints(0);
    punkty[3] = gracz_2->getMelee()->getPoints(0);
    punkty[4] = gracz_2->getRanged()->getPoints(0);
    punkty[5] = gracz_2->getSiege()->getPoints(0);

    p1_pkt = punkty[0] + punkty[1] + punkty[2];
    p2_pkt = punkty[3] + punkty[4] + punkty[5];

    punkty[6] = gracz_1->getDeck()->getDeckSize();
    punkty[7] = gracz_2->getDeck()->getDeckSize();
    punkty[8] = gracz_1->getReka()->getDeckSize();
    punkty[9] = gracz_2->getReka()->getDeckSize();

    punkty[10] = p1_gamescore;
    punkty[11] = p2_gamescore;

    nakazAktualizacjiPunkt(punkty);
}

void gra::graczPas(int nr_gr) {
    if (nr_gr == 1 && GameState == Tura1) {
        gracz_1->Pasuj();
        if (gracz_2->isPas()) {
            koniec_rundy();
        }
        else {
            GameState = Tura2;
            QTimer::singleShot(1000, this, &gra::tura_bota);
        }
    }
    else if (nr_gr == 2 && GameState == Tura2) {
        gracz_2->Pasuj();
        if (gracz_1->isPas()) {
            koniec_rundy();
        }
        else {
            GameState = Tura1;
        }
    }
}
void gra::clearPlansza() {
    gracz_1->wyczysc();
    gracz_2->wyczysc();
    redrawBoard();
}
