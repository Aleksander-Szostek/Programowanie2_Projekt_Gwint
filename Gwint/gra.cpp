#include "gra.h"
#include "bot_player.h"
#include "human_player.h"
#include "karta.h"
#include <QPushButton>
#include <QLayout>
#include "i_constant_valuse.h"


gra::gra() {
    gracz_1 = new human_player; // musimy zrbic klase np gracz_player
    gracz_2 = new bot_player;
}

void gra::zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2){
    std::srand(time(NULL));
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

    if (GameState == Tura2) {
        QTimer::singleShot(1000, this, &gra::tura_bota);
    }
}

void gra::koniec_rundy(){
    GameState = KoniecRundy;

    nr_rundy ++;

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

    countPoints();
    nakazZmianyStrony(2);

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

    gracz_1 = new human_player;
    gracz_2 = new bot_player;

    delete temp_p1;
    delete temp_p2;

    nr_rundy = 0;

    qDebug() << "Koniec gry";
}

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
    switch (karta_g->getKeyword()) {
        case Szpieg:{
            szpieg(karta_g, nr_gracza);
            break;
        }

        case Przyzwij:{
            przyzwij(karta_g, nr_gracza);
            break;
        }

        case Linked:{
            linked(karta_g, nr_gracza);
            break;
        }

        case Medyk:{
            medyk(karta_g, nr_gracza);
            break;
        }

        case Pogoda:{
            pogodaPlay(karta_g, nr_gracza);
            break;
        }

        case Porzoga:{
            porzoga(karta_g, nr_gracza);
            break;
        }

        case Horn:{
            horn(karta_g, nr_gracza);
            break;
        }

        case Boost:{
            boost(karta_g, nr_gracza);
            break;
        }

        case Grzyb:{
            grzyb(karta_g, nr_gracza);
            break;
        }

        default:
            break;
    }

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

void gra::gameClear() {
    gracz_1->wyczysc();
    gracz_2->wyczysc();
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
    //tutaj będzie trzeba dodać implementacje
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
StanGry gra::getGameState() {
    return GameState;
}
int gra::getNrRundy() {
    return nr_rundy;
}


/*
keyword::lokacjaKarty gra::sygnalSzukaj(int ID, RzadPlanszy gdzieSzukac){
    keyword::lokacjaKarty znalezione;
    znalezione.miejsce = Unknown;

    kontener_kart* adres;

    for (int i = 0 ; i > adres->getDeckSize() ; i++) {
        if (adres->getKartaFromList(i)->getID() == ID) {
            znalezione.indeks = i;
            znalezione.miejsce = gdzieSzukac;
            break;
        }
    }

    return znalezione;
}
*/

kontener_kart* gra::getKontenerByEnum(RzadPlanszy rzad) {

    kontener_kart* kontener = nullptr;
    switch (rzad) {
        case P1_Melee: {
            kontener = gracz_1->getMelee();
            break;
        }
        case P1_Range: {
            kontener = gracz_1->getRanged();
            break;
        }
        case P1_Siege: {
            kontener = gracz_1->getSiege();
            break;
        }
        case P2_Melee: {
            kontener = gracz_2->getMelee();
            break;
        }
        case P2_Range: {
            kontener = gracz_2->getRanged();
            break;
        }
        case P2_Siege: {
            kontener = gracz_2->getSiege();
            break;
        }
        case P1_Spell: {
            kontener = nullptr;
            break;
        }
        case P2_Spell: {
            kontener = nullptr;
            break;
        }
        case P1_Leader: {
            kontener = nullptr;
            break;
        }
        case P2_Leader: {
            kontener = nullptr;
            break;
        }
        case P1_Hand: {
            kontener = gracz_1->getReka();
            break;
        }
        case P2_Hand: {
            kontener = gracz_1->getReka();
            break;
        }
        case P1_Deck: {
            kontener = gracz_1->getDeck();
            break;
        }
        case P2_Deck: {
            kontener = gracz_2->getDeck();
            break;
        }
        default: {
            kontener = nullptr;
        }
    }

return kontener;
}

void gra::szpieg(karta* active, int nr_gracza){
    qDebug() << "Szpiegowanie";

    dobierzKarte(nr_gracza, 2);

    rzedy_enum konwersje;
    RzadPlanszy lokacja = konwersje.convertTypToRzad(active->getKategoria(), nr_gracza);

    moveCardByEnum(lokacja , konwersje.reverseRzad(lokacja) , active->getID());
}

void gra::przyzwij(karta* active, int nr_gracza){
    qDebug() << "Przyzywanie";

    player* gracz;



    qDebug() << "wybieranie gracza";
    if (nr_gracza == 1)
        gracz = gracz_1;
    else
        gracz = gracz_2;

    deck* talia = gracz->getDeck();

    int size = active->getCele().size();

    //dobiera karty z talii do natychmiastowego zagrania
    qDebug() << "Sprawdzanie talii";
    for (int indeks = talia->getDeckSize() - 1; indeks >= 0 ; indeks--) {
        for (int cel = 0; cel < size; cel++) {
            if (active->getCele().at(cel) == talia->getKartaFromList(indeks)->getID()) {
                talia->move_card(indeks, gracz->getReka());
            }
        }
    }

    qDebug() << "Zagrywanie syfu";
    player_hand *reka = gracz->getReka();
    for (int indeks = gracz->getReka()->getDeckSize() - 1; indeks >= 0 ; indeks--) {
        for (int cel = 0; cel < size; cel++) {
            if (active->getCele().at(cel) == reka->getKartaFromList(indeks)->getID()
                && indeks < gracz->getReka()->getDeckSize()) {
                //dodatkowy warunek musi być sprawdzany bo każda karta aktywuje swój efekt
                //więc inaczej by zagrywało n^2 kart zamiast n kart
                //(przyzywało całą artylerię imperium ludzkości)
                globalCardPlayed(gracz->zagrajKarte(indeks), nr_gracza);
            }
        }
    }
}

void gra::linked(karta* active, int nr_gracza){

}

void gra::medyk(karta* active, int nr_gracza){

}

void gra::rebornDEAD(karta* active, int nr_gracza){

}

void gra::porzoga(karta* active, int nr_gracza){

}

void gra::pogodaPlay(karta* active, int nr_gracza){

}

void gra::horn(karta* active, int nr_gracza){

}

void gra::boost(karta* active, int nr_gracza){

}

void gra::grzyb(karta* active, int nr_gracza){

}

void gra::moveCardByEnum(RzadPlanszy rzad_start, RzadPlanszy rzad_end, int ID){
    int indeks = findCardByID(rzad_start, ID);

    if (indeks >= 0) {
        kontener_kart* lokacja_start = getKontenerByEnum(rzad_start);
        kontener_kart* lokacja_end = getKontenerByEnum(rzad_end);
        lokacja_start->move_card(indeks, lokacja_end);
    }
}

int gra::findCardByID(RzadPlanszy rzad, int ID) {
    int indeks = -1;
    kontener_kart* lokacja = getKontenerByEnum(rzad);

    for (int i = 0 ; i < lokacja->getDeckSize() ; i++) {
        if (lokacja->getKartaFromList(i)->getID() == ID) {
            indeks = i;
            break;
        }
    }

    return indeks;
}