#include "plansza_linia.h"

plansza_linia::plansza_linia() {
    horn = new kontener_kart;
}

void plansza_linia::emptyLinia(){
    Ciag_kart.clear();
}

int plansza_linia::getPoints(bool Pogoda){
    int sum = 0;
    bool isHorned = getHornBool();
    testBoost();

    for (int i = 0; i < Ciag_kart.size(); i++) {
        int selfBoost = 0;
        if (Ciag_kart[i]->getKeyword() == Boost)
            selfBoost = 1;

        if (Ciag_kart[i]->getKeyword() == Linked)
            updateSilaBraterstwa(i, Pogoda, isHorned, boost - selfBoost);
        else
            Ciag_kart[i]->updateSila( Pogoda , isHorned , boost - selfBoost );

        sum +=Ciag_kart[i]->getSila();
    }
    return sum;
}

kontener_kart* plansza_linia::getHorn(){
    return horn;
}

bool plansza_linia::getHornBool(){
    if (getHorn()->getKartaFromList(0) != nullptr) {
        if (getHorn()->getKartaFromList(0)->getKeyword() == Horn)
            return true;
    }
    else if (isHorny())
        return true;
    return false;
}

bool plansza_linia::isHorny() {
    bool warunek = false;

    for (int i = 0 ; i < Ciag_kart.size() ; i++) {
        if (Ciag_kart[i]->getKeyword() == Horn) {
            warunek = true;
            break;
        }
    }

    return warunek;
}

void plansza_linia::updateSilaBraterstwa(int indeks, bool pogoda, bool horn, int boost) {

    int bracia = 0;
    karta* brat = Ciag_kart[indeks];

    for (int i = 0 ; i < Ciag_kart.size() ; i++) {
        for (int j = 0 ; ( j < brat->getCele().size() ) && ( i != indeks ) ; j++) {
            if (Ciag_kart[i]->getID() == brat->getCele().at(j))
                bracia++;
        }
    }

    brat->updateSila( pogoda , horn , boost , bracia);
}

void plansza_linia::testBoost() {
    boost = 0;

    for (int i = 0 ; i < Ciag_kart.size() ; i++) {
        if (Ciag_kart[i]->getKeyword() == Boost)
            boost++;
    }
}