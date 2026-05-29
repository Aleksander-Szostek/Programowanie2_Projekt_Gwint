#include "player.h"

player::player() {
    Talia = new deck;
    reka = new player_hand;
    melee_l = new plansza_linia;
    ranged_l = new plansza_linia;
    siege_l = new plansza_linia;
    cmentarzysko = new graveyard;
}

plansza_linia* player::getMelee(){
    return melee_l;
}

plansza_linia* player::getRanged(){
    return ranged_l;
}

plansza_linia* player::getSiege(){
    return siege_l;
}

deck* player::getDeck(){
    return Talia;
}

player_hand* player::getReka(){
    return reka;
}

void player::dobierzKarte(){
    if (Talia->getDeckSize() > 0)
        Talia->move_card(0, reka);
}

karta* player::zagrajKarte(int nr_w_rece){
    qDebug() << "Gracz zagrał lokalnie. nr: " + QString::number(nr_w_rece);
    Kategoria typ_karty = reka->getKartaFromList(nr_w_rece)->getKategoria();
    qDebug() << "Zapisywanie pointera";
    karta* karta_g = reka->getKartaFromList(nr_w_rece);

    qDebug() << "Sprawdzanie lokacji";
    if (typ_karty == Kategoria::Melee){
        reka->move_card(nr_w_rece, melee_l);
        qDebug("Zagrano melee");
    }
    else if (typ_karty == Kategoria::Ranged){
        reka->move_card(nr_w_rece, ranged_l);
        qDebug("Zagrano ranged");
    }
    else if (typ_karty == Kategoria::Siege){
        reka->move_card(nr_w_rece, siege_l);
        qDebug("Zagrano siege");
    }
    else if (typ_karty == Kategoria::Spell){
        qDebug("Zagrano zaklęcie (idzie do shadow realm)");
        //reka->delete_card(nr_w_rece);
    }
    else if (typ_karty == Kategoria::Agile){
        qDebug("Zagrano agile (idzie do shadow realm)");
    }
    else {
        qDebug("Zagrana karta nie ma typu.");
        reka->delete_card(nr_w_rece);
    }

    qDebug() << "Zwracanie card ptr";
    return karta_g;
}

void player::uzyjLidera(){

}
//zmieniłem na te dwie funkcje bo tamto było jakieś dziwne i nie działało z jakiegoś powodu (nadal nie działa)
void player::Pasuj(){
    czyPas = true;
}

void player::ResetPasa(){
    czyPas = false;
}

bool player::isPas(){
    return czyPas;
}

void player::startRundy(){
    melee_l->emptyLinia();
    ranged_l->emptyLinia();
    siege_l->emptyLinia();

    czyPas = false;
}

void player::wyczysc() {
    while (melee_l->getDeckSize() > 0) {
        melee_l->move_card(0 , cmentarzysko);
    }

    while (ranged_l->getDeckSize() > 0) {
        ranged_l->move_card(0 , cmentarzysko);
    }

    while (siege_l->getDeckSize() > 0) {

        siege_l->move_card(0 , cmentarzysko);
    }
}


void player::getPoints(int return_val[3], bool Pogoda[3]){
    return_val[0] = melee_l->getPoints(Pogoda[0]);
    return_val[1] = ranged_l->getPoints(Pogoda[1]);
    return_val[2] = siege_l->getPoints(Pogoda[2]);
}


void player::setPunktyK(int a){
    punkty=a;
}

int player::getPunktyK(){
    return punkty;
}
