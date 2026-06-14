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
    pogoda = new efekty_pogodowe;

    static_cast<bot_player*>(gracz_2)->setPogodaStol(pogoda);
}

void gra::zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2){
    std::srand(time(NULL));
    gracz_1->getDeck()->makeDeck(nazwa_talii_1);
    qDebug()<<"talia gracza to: "<<nazwa_talii_1;
    gracz_2->getDeck()->makeDeck(nazwa_talii_2);
    qDebug()<<"talia bota to: "<<nazwa_talii_1;
//    gracz_1->getDeck()->validifyDeck();
//    gracz_2->getDeck()->validifyDeck();
    if (gracz_1->getDeck()->DeckValid && gracz_2->getDeck()->DeckValid) {
        int losowanie_start = rand()%2 + 1;
            if (losowanie_start == 1) {
                GameState = Tura1;
                qDebug() << "Tura 1";

            }
            else {
                GameState = Tura2;
                qDebug() << "Tura 2";
                QTimer::singleShot(1000, this, &gra::tura_bota);
            }
    }
    else {
        qDebug() << "Invalid deck";
        koniec_gry();
    }

    dobierzKarte(1, startHand);
    dobierzKarte(2, startHand);

    // if (GameState == Tura2) {

    // }
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
        qDebug() << "Gra nierozpoczęta ze względu na niewłaściewość 1 z talii";
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

void gra::graczZagrajKarte(int nr_w_rece, int nr_gracza) {

    qDebug() << "Czyszczenie selekcji";
    gracz_1->setPendingSelection();
    gracz_2->setPendingSelection();

    if (nr_gracza == 1 && GameState == Tura1){

        qDebug() << "Gracz 1 zagrywać bedzie";
        globalCardPlayed(gracz_1->zagrajKarte(nr_w_rece), 1);

        redrawBoard();

        if ((!gracz_2->isPas()) && gracz_1->getPendingSelection() < 0){
            GameState = Tura2;
            QTimer::singleShot(1000, this, &gra::tura_bota);
        }
    }
    else if (nr_gracza == 2 && GameState == Tura2){

        qDebug() << "Gracz 2 zagrywać bedzie";
        globalCardPlayed(gracz_2->zagrajKarte(nr_w_rece), 2);

        redrawBoard();

        if ((!gracz_1->isPas()) && gracz_2->getPendingSelection() < 0){
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
    qDebug() << "Globalnie zagrał: " + QString::number(nr_gracza);
    if (karta_g == nullptr)
        return;

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

        case Kukla:{
            player* gracz = getGracz(nr_gracza);
            if(nr_gracza == 1){
                qDebug() << "Ustawianie selekcji";
                gracz->setPendingSelection(0);
            }
            //dodaje to bo bot wczesniej nie mial fizycznie jak zagrac kukly
            else if(nr_gracza==2){
                qDebug()<<"Bot zagrywa kukle";
                bot_player* bot = static_cast<bot_player*>(gracz);
                std::vector<karta*> kartyBota = bot->pobierzWszyskieKarty(bot);
                if (kartyBota.empty()==true){
                    return;
                }
                karta* celKarty = nullptr;
                for (auto* j : kartyBota) {
                    if (j->getKeyword() == Szpieg) {
                        celKarty = j;
                        break;
                    }
                }

                // najpierw sprawdza czy nie ma szpiegow do podmiany
                if (celKarty == nullptr) {
                    int maxSila = -1;
                    for (auto* i : kartyBota) {
                        if (i->getSila() > maxSila && i->getLeg() != true && i->getKategoria() != Spell) {
                            maxSila = i->getSila();
                            celKarty = i;
                        }
                    }
                }
                if (celKarty != nullptr) {
                    RzadPlanszy rzadCelu;
                    int indeksCelu = -1;
                    RzadPlanszy rzedyBota[] = { P2_Melee, P2_Range, P2_Siege };
                    for (RzadPlanszy rzad : rzedyBota) {
                        int idx = findCardByID(rzad, celKarty->getID());
                        if (idx >= 0) {
                            rzadCelu = rzad;
                            indeksCelu = idx;
                            break;
                        }
                    }

                    if (indeksCelu >= 0) {
                        int indeksKuklyWRece = gracz->getPendingSelection();
                        kukla(indeksKuklyWRece, rzadCelu, indeksCelu, 2);

                        gracz->setPendingSelection(-1);
                    }
                }
            }

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

    emit nakazCzyszczeniaLayoutu(P1_Melee_Horn);
    emit nakazCzyszczeniaLayoutu(P1_Range_Horn);
    emit nakazCzyszczeniaLayoutu(P1_Siege_Horn);
    emit nakazCzyszczeniaLayoutu(P2_Melee_Horn);
    emit nakazCzyszczeniaLayoutu(P2_Range_Horn);
    emit nakazCzyszczeniaLayoutu(P2_Siege_Horn);

    emit nakazCzyszczeniaLayoutu(Weather);
    emit nakazCzyszczeniaLayoutu(P1_Leader);
    emit nakazCzyszczeniaLayoutu(P2_Leader);
    emit nakazCzyszczeniaLayoutu(P1_Hand);

    qDebug() << "Czyszczenie wszystkiego";
}

void gra::redrawBoard() {

    clearBoard();

    countPoints();

    if (GameState != KoniecGry) {

    qDebug() << "Przerysowywanie planszy";

    redrawLine(P1_Melee);
    redrawLine(P1_Range);
    redrawLine(P1_Siege);
    redrawLine(P2_Melee);
    redrawLine(P2_Range);
    redrawLine(P2_Siege);

    qDebug() << "Narysowano linie";

    redrawLine(P1_Melee_Horn);
    redrawLine(P1_Range_Horn);
    redrawLine(P1_Siege_Horn);
    redrawLine(P2_Melee_Horn);
    redrawLine(P2_Range_Horn);
    redrawLine(P2_Siege_Horn);

    qDebug() << "Narysowano rogi";

    redrawLine(P1_Hand);
    redrawLine(P1_Leader);
    redrawLine(P2_Leader);
    redrawLine(Weather);

    qDebug() << "Narysowano wszystko";

    countPoints();

    }
}

void gra::redrawLine(RzadPlanszy gdzieRysowac) {
    kontener_kart* Linia = getKontenerByEnum(gdzieRysowac);

    rzedy_enum konwersje;
    int nr_gracza = 2;
    if (konwersje.isPlayer1(gdzieRysowac))
        nr_gracza = 1;

    for (int i = 0; i < Linia->getDeckSize(); i++) {
        karta* daneKarty = Linia->getKartaFromList(i);
        emit nakazRysowaniaKarty(daneKarty, gdzieRysowac, i, nr_gracza);
    }
}

void gra::gameClear() {
    gracz_1->wyczysc();
    gracz_2->wyczysc();
    redrawBoard();
}

void gra::dobierzKarte(int nr_gracza, int n) {
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

void gra::wybranoKarte(RzadPlanszy lokacja, int indeks ){
    qDebug() << "Wybrano karte";

    player* gracz = nullptr;
    int nr_gracza = 0;
    if (GameState == Tura1) {
        gracz = gracz_1;
        nr_gracza = 1;
        qDebug() << "Sprawdzanie selekcji gracza 1";
    }
    else if (GameState == Tura2) {
        gracz = gracz_2;
        nr_gracza = 2;
        qDebug() << "Sprawdzanie selekcji gracza 1";
    }
    else
        return;

    int indeks_aktora = gracz->getPendingSelection();
    qDebug() << "Indeks aktora: " + QString::number(indeks_aktora);
    if (indeks_aktora < 0) {
        qDebug() << "Brak selekcji";
        return;
    }

    karta* aktor = gracz->getReka()->getKartaFromList(indeks_aktora);

    switch (aktor->getKeyword()) {
    case Kukla: {
        qDebug() << "Kukła zagrywa sie";
        if (getKontenerByEnum(lokacja)->getKartaFromList(indeks)->getLeg() == true ||
            getKontenerByEnum(lokacja)->getKartaFromList(indeks)->getKategoria() == Spell)
        {
            qDebug() << "Wybrano kartę legendarną. Nic się nie dzieje.";
            return;
        }

        kukla(indeks_aktora, lokacja, indeks, nr_gracza);
        graczZagrajKarte(-10, nr_gracza);   //zagrywam fikcyjną kartę żeby uruchomić sekwecję zakończenia tury
    }
    default: {
        break;
    }
    }
}

void gra::wybranoLinie(RzadPlanszy lokacja) {
    player* gracz = nullptr;
    RzadPlanszy reka;
    int nr_gracz;
    if (GameState == Tura1) {
        gracz = gracz_1;
        reka = P1_Hand;
        nr_gracz = 1;
    }
    else if (GameState == Tura2) {
        gracz = gracz_2;
        reka = P2_Hand;
        nr_gracz = 2;
    }
    else
        return;

    qDebug() << "Wybrano linie";

    int indeks_aktora = gracz->getPendingSelection();
    karta* aktor = gracz->getReka()->getKartaFromList(indeks_aktora);

    switch (aktor->getKeyword()) {
    case Horn: {
        RzadPlanszy rog_poz;
        switch (lokacja) {
        case P1_Melee: {
            rog_poz = P1_Melee_Horn;
            break;
        }
        case P1_Range: {
            rog_poz = P1_Range_Horn;
            break;
        }
        case P1_Siege: {
            rog_poz = P1_Siege_Horn;
            break;
        }
        case P2_Melee: {
            rog_poz = P2_Melee_Horn;
            break;
        }
        case P2_Range: {
            rog_poz = P2_Range_Horn;
            break;
        }
        case P2_Siege: {
            rog_poz = P2_Siege_Horn;
            break;
        }
        default: {
            return;
        }
        }

        moveCardByEnum(reka, rog_poz, aktor->getID());
        graczZagrajKarte(-10, nr_gracz);
        break;
    }
    case Grzyb: {
        kontener_kart* linia = getKontenerByEnum(lokacja);
        for (int i = linia->getDeckSize() - 1; i >= 0 ; i--) {
            if (linia->getKartaFromList(i)->getKeyword() == Morph) {
                linia->move_card(i, gracz->getLimbo());
            }
        }

        for(int i = 0; i < gracz->getLimbo()->getDeckSize(); i++) {
            gracz->getLimbo()->getKartaFromList(i)->setKeyword("REBIRTH");
        }

        clearLimbo();

        gracz->getReka()->delete_card(indeks_aktora);
        graczZagrajKarte(-10, nr_gracz);

        break;
    }
    default: {
        break;
    }
    }
}

void gra::countPoints() {
    int punkty[12];

    punkty[0] = gracz_1->getMelee()->getPoints(pogoda->isMeleePogoda());
    punkty[1] = gracz_1->getRanged()->getPoints(pogoda->isRangePogoda());
    punkty[2] = gracz_1->getSiege()->getPoints(pogoda->isSiegePogoda());
    punkty[3] = gracz_2->getMelee()->getPoints(pogoda->isMeleePogoda());
    punkty[4] = gracz_2->getRanged()->getPoints(pogoda->isRangePogoda());
    punkty[5] = gracz_2->getSiege()->getPoints(pogoda->isSiegePogoda());

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
    pogoda->wyczysc();
    clearLimbo();
    redrawBoard();
}
StanGry gra::getGameState() {
    return GameState;
}
int gra::getNrRundy() {
    return nr_rundy;
}

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
            kontener = gracz_1->getDeck()->getLeader();
            break;
        }
        case P2_Leader: {
            kontener = gracz_2->getDeck()->getLeader();
            break;
        }
        case P1_Hand: {
            kontener = gracz_1->getReka();
            break;
        }
        case P2_Hand: {
            kontener = gracz_2->getReka();
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
        case P1_Graveyard: {
            kontener = gracz_1->getGraveyard();
            break;
        }
        case P2_Graveyard: {
            kontener = gracz_2->getGraveyard();
            break;
        }
        case P1_Limbo: {
            kontener = gracz_1->getLimbo();
            break;
        }
        case P2_Limbo: {
            kontener = gracz_2->getLimbo();
            break;
        }
        case Weather: {
            kontener = pogoda;
            break;
        }
        case P1_Melee_Horn: {
            kontener = gracz_1->getMelee()->getHorn();
            break;
        }
        case P1_Range_Horn: {
            kontener = gracz_1->getRanged()->getHorn();
            break;
        }
        case P1_Siege_Horn: {
            kontener = gracz_1->getSiege()->getHorn();
            break;
        }
        case P2_Melee_Horn: {
            kontener = gracz_2->getMelee()->getHorn();
            break;
        }
        case P2_Range_Horn: {
            kontener = gracz_2->getRanged()->getHorn();
            break;
        }
        case P2_Siege_Horn: {
            kontener = gracz_2->getSiege()->getHorn();
            break;
        }
        default: {
            qDebug() << "Nie znaleziono kontenera.";
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

    player* gracz = getGracz(nr_gracza);

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
    qDebug() << "Zagrano bratka";
}
void gra::medyk(karta* active, int nr_gracza){

}
void gra::rebornDEAD(karta* active, int nr_gracza){

}
void gra::porzoga(karta* active, int nr_gracza){

    qDebug() << "Pożoga aktywowana.";
    int sila_max = 0;
    std::vector<Lokacje> hit_list;

    porzogaTestLinia(P1_Melee, hit_list, sila_max);
    porzogaTestLinia(P1_Range, hit_list, sila_max);
    porzogaTestLinia(P1_Siege, hit_list, sila_max);
    porzogaTestLinia(P2_Melee, hit_list, sila_max);
    porzogaTestLinia(P2_Range, hit_list, sila_max);
    porzogaTestLinia(P2_Siege, hit_list, sila_max);

    for (int i = hit_list.size() - 1; i >= 0 ; i--) {
        kill(hit_list[i].rzad, hit_list[i].indeks);
        qDebug () << "koniec pętli";
    }

    if (active->getKategoria() == Spell) {
        RzadPlanszy reka;
        RzadPlanszy limbo;

        if (nr_gracza == 1) {
            reka = P1_Hand;
            limbo = P1_Limbo;
        }
        else if (nr_gracza == 2) {
            reka = P2_Hand;
            limbo = P2_Limbo;
        }

        moveCardByEnum(reka, limbo, active->getID());
    }

    clearLimbo();
}
void gra::pogodaPlay(karta* active, int nr_gracza){
    RzadPlanszy reka_g;
    if (nr_gracza == 1)
        reka_g = P1_Hand;
    else if (nr_gracza == 2)
        reka_g = P2_Hand;
    else
        return;

    moveCardByEnum(reka_g, Weather, active->getID());

    if (active->getID() == 6) {     // 6 to ID czystego nieba
        pogoda->wyczysc();
    }
}
void gra::horn(karta* active, int nr_gracza){
    qDebug() << "Zagrano róg";
}
void gra::boost(karta* active, int nr_gracza){
    qDebug() << "Zagrano boościarza";
}
void gra::grzyb(karta* active, int nr_gracza){
    player* gracz = getGracz(nr_gracza);
    qDebug() << "Zagrano grzybiarza";
    kontener_kart* linia;
    switch (active->getKategoria()) {
    case Melee: {
        linia = gracz->getMelee();
        break;
    }
    case Ranged: {
        linia = gracz->getRanged();
        break;
    }
    case Siege: {
        linia = gracz->getSiege();
        break;
    }
    default:
        return;
    }

    for (int i = linia->getDeckSize() - 1; i >= 0 ; i--) {
        if (linia->getKartaFromList(i)->getKeyword() == Morph) {
            linia->move_card(i, gracz->getLimbo());
        }
    }

    for(int i = 0; i < gracz->getLimbo()->getDeckSize(); i++) {
        gracz->getLimbo()->getKartaFromList(i)->setKeyword("REBIRTH");
    }

    clearLimbo();
    return;
}
void gra::kukla(int indeks_reki, RzadPlanszy miejsce_celu, int indeks_celu, int nr_gracza){

    player* gracz = getGracz(nr_gracza);
    RzadPlanszy reka_gracz;

//    karta* kukla = gracz->getReka()->getKartaFromList(indeks_reki);

    gracz->getReka()->move_card(indeks_reki, gracz->getLimbo());
    getKontenerByEnum(miejsce_celu)->move_card(indeks_celu, gracz->getReka());

    gracz->getLimbo()->move_card(0, getKontenerByEnum(miejsce_celu));
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

void gra::porzogaTestLinia(RzadPlanszy badane, std::vector<Lokacje> &lista, int &sila_max) {
    for (int i = 0; i < getKontenerByEnum(badane)->getDeckSize(); i++) {
        if (getKontenerByEnum(badane)->getKartaFromList(i)->getSila() > sila_max
            && getKontenerByEnum(badane)->getKartaFromList(i)->getLeg() != true) {

            sila_max = getKontenerByEnum(badane)->getKartaFromList(i)->getSila();

            Lokacje karta;
            karta.indeks = i;
            karta.rzad = badane;
            lista.clear();
            lista.push_back(karta);
        }
        else if (getKontenerByEnum(badane)->getKartaFromList(i)->getSila() == sila_max
                 && getKontenerByEnum(badane)->getKartaFromList(i)->getLeg() != true) {

            Lokacje karta;
            karta.indeks = i;
            karta.rzad = badane;
            lista.push_back(karta);
        }
    }
}

void gra::kill(RzadPlanszy rzad, int indeks) {

    kontener_kart* Linia = getKontenerByEnum(rzad);
    //karta* mordowana = Linia->getKartaFromList(indeks);
    rzedy_enum konwersja;
    if (konwersja.isPlayer1(rzad)) {
        qDebug() << "Mordowanie u gracza 1." + Linia->getKartaFromList(indeks)->getNazwa() + QString::number(indeks);
        Linia->move_card(indeks, getKontenerByEnum(P1_Limbo));
    }
    else {
        qDebug() << "Mordowanie u gracza 2." + Linia->getKartaFromList(indeks)->getNazwa() + QString::number(indeks);
        Linia->move_card(indeks, getKontenerByEnum(P2_Limbo));
    }
}

void gra::clearLimbo() {
    qDebug() << "Czyszczenie Limbo";

    kontener_kart* Limbo = getKontenerByEnum(P1_Limbo);
    int size = Limbo->getDeckSize();
    card_loader* nekromanta = new card_loader;

    for (int i = size - 1 ; i >= 0 ; i--) {
        if (Limbo->getKartaFromList(i)->getKeyword() == Reborn) {
            karta* new_karta = new karta;
            nekromanta->zaladuj_karte(Limbo->getKartaFromList(i)->getCele().at(0), new_karta);
            qDebug() << "Załadowano dziedzica: " + new_karta->getNazwa();

            Limbo->move_card(i, getKontenerByEnum(P1_Graveyard));

            getKontenerByEnum(P1_Hand)->add_card_to(new_karta, 0);
            globalCardPlayed(gracz_1->zagrajKarte(0) , 1);
        }

        else
            Limbo->move_card(i, getKontenerByEnum(P1_Graveyard));
    }

    Limbo = getKontenerByEnum(P2_Limbo);
    size = Limbo->getDeckSize();

    for (int i = size - 1 ; i >= 0 ; i--) {
        if (Limbo->getKartaFromList(i)->getKeyword() == Reborn) {
            karta* new_karta = new karta;
            nekromanta->zaladuj_karte(Limbo->getKartaFromList(i)->getCele().at(0), new_karta);  //Ładuje do pamięci karte do zagrania.
            Limbo->move_card(i, getKontenerByEnum(P2_Graveyard));   //przed aktywacją wskszeszenia wywalam karte do cmentarza żeby nie powstała nieprzewidziana pętla
            getKontenerByEnum(P2_Hand)->add_card_to(new_karta, 0);  //doaje karte bozpośrednio na początek przy użyciu funkcji która nie tasuje
            globalCardPlayed(gracz_2->zagrajKarte(0) , 2);
        }

        else {
            Limbo->move_card(i, getKontenerByEnum(P2_Graveyard));
        }
    }

    delete nekromanta;
}

player* gra::getGracz(int nr) {
    player *gracz = nullptr;
    if (nr == 1)
        gracz = gracz_1;
    else if (nr == 2)
        gracz = gracz_2;

    return gracz;
}
