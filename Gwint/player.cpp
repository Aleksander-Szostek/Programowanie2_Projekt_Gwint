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
    Kategoria typ_karty = reka->getKartaFromList(nr_w_rece)->getKategoria();

    karta* karta_g = nullptr;

    if (typ_karty == Kategoria::Melee){
        reka->move_card(nr_w_rece, melee_l);
    }
    else if (typ_karty == Kategoria::Ranged){
        reka->move_card(nr_w_rece, ranged_l);
    }
    else if (typ_karty == Kategoria::Siege){
        reka->move_card(nr_w_rece, siege_l);
    }
    else if (typ_karty == Kategoria::Spell){
        karta_g = reka->getKartaFromList(nr_w_rece);
        qDebug("Zagrano zaklęcie (idzie do shadow realm)");
    }
    else if (typ_karty == Kategoria::Agile){
        karta_g = reka->getKartaFromList(nr_w_rece);
        qDebug("Zagrano agile (idzie do shadow realm)");
    }
    else {
        qDebug("Zagrana karta nie ma typu.");
    }

    return karta_g;
}

void player::uzyjLidera(){

}

void player::Spasuj(){
    czyPas = true;
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