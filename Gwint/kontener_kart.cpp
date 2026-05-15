#include "kontener_kart.h"

kontener_kart::kontener_kart() {}

void kontener_kart::add_card_to(karta* dodawana_karta, int pozycja){
    Ciag_kart.insert(std::next(Ciag_kart.begin(), pozycja), dodawana_karta);
    return;
}

void kontener_kart::move_card(int poz_start, kontener_kart *output_list){
    output_list->add_card_to(Ciag_kart[poz_start], 0);
    if (output_list->isDeck)                  //jeśli przekładamy kartę do posortowanej talii to ją jeszcze raz tasujemy
        output_list->shulfe_list();             //używane do muliganu
    else
        output_list->sort_list();               //jeśli dodajemy do innego to listę układamy w kolejności

    delete_card(poz_start);
    return;
}

void kontener_kart::delete_card(int pozycja){
    Ciag_kart.erase(std::next(Ciag_kart.begin(), pozycja));
    return;
}

void kontener_kart::shulfe_list(){
    return;
}

void kontener_kart::sort_list(){
    std::sort(Ciag_kart.begin(),Ciag_kart.end(),
            [](karta *a, karta *b){return a->getID() < b->getID();});
            //wygląda dziwnie ale (ponoc) działa
    //przydałoby się tu dac jeszcze żeby karty ze sobą powiązane były obok siebie
    //ale to by wymagało 2 sortowań już (najpierw po powiązaniu a potem po ID i powiązaniu)
    return;
}

int kontener_kart::getDeckSize(){
    return Ciag_kart.size();
}

karta* kontener_kart::getKartaFromList(int poz) {
    return Ciag_kart[poz];
}