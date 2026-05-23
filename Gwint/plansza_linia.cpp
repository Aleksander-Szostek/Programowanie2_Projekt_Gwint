#include "plansza_linia.h"

plansza_linia::plansza_linia() {

}

void plansza_linia::emptyLinia(){
    Ciag_kart.clear();
}

int plansza_linia::getPoints(bool Pogoda){
    int sum = 0;
    bool isHorned = getHornBool();
    for (int i = 0; i < Ciag_kart.size(); i++) {
        Ciag_kart[i]->updateSila( 0 , isHorned , 0 );
        sum +=Ciag_kart[i]->getSila();
    }
    return sum;
}

karta* plansza_linia::getHorn(){
    if (horn.getDeckSize() == 0)
        return nullptr;

    return horn.getKartaFromList(0);
}

bool plansza_linia::getHornBool(){
    if (getHorn() == nullptr)
        return false;
    else
        return true;
}