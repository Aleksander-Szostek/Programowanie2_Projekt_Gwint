#include "player.h"

player::player() {}

void player::dobierzKarte(){
    Talia->move_card(0, reka);
}

void player::zagrajKarte(int nr_w_rece){
    Kategoria typ_karty = reka->getKartaFromList(nr_w_rece)->getKategoria();

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

    }
    else if (typ_karty == Kategoria::Agile){

    }
    else {
        //tutaj ma wywalić errora
    }

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