#include "karta.h"

karta::karta() {}

void karta::setID(unsigned int id_s){
    id = id_s;
    return;
}
void karta::setName(QString nazwa_s){
    nazwa = nazwa_s;
    return;
}
void karta::setFrakcja(QString Nazwa_frakcji){
    if (Nazwa_frakcji == "NORTHERN")
        frakcja = Frakcja::Polnoc;
    else if (Nazwa_frakcji == "SCOIA'TAEL")
        frakcja = Frakcja::Elfy;
    else if (Nazwa_frakcji == "MONSTERS")
        frakcja = Frakcja::Potwory;
    else if (Nazwa_frakcji == "NILFGAARD")
        frakcja = Frakcja::Nilfgard;
    else if (Nazwa_frakcji == "SKELLIGE")
        frakcja = Frakcja::Skelige;
    else
        frakcja = Frakcja::Neutral;
    return;
}
void karta::setKategoria(QString Nazwa_kategorii){
    if (Nazwa_kategorii == "MELEE")
        kategoria = Kategoria::Melee;
    else if (Nazwa_kategorii == "RANGED")
        kategoria = Kategoria::Ranged;
    else if (Nazwa_kategorii == "SIEGE")
        kategoria = Kategoria::Siege;
    else if (Nazwa_kategorii == "SPELL")
        kategoria = Kategoria::Spell;
    else if (Nazwa_kategorii == "LEADER")
        kategoria = Kategoria::Leader;
    else if (Nazwa_kategorii == "AGILE")
        kategoria = Kategoria::Agile;
    else {
        kategoria = Kategoria::Undefined;
        setName("Error: niezdefiniowany typ karty");
    }
    return;
}

void karta::setSilaBaz(unsigned int sila_bazowa_s){
    sila_bazowa = sila_bazowa_s;
    return;
}
void karta::setKeywordAdress(keyword* efekt_s){
    efekt = efekt_s;
    return;
}
void karta::setCele(std::vector<int> cele_s){
    cele = cele_s;
    return;
}
void karta::setMax(unsigned int max_w_talii_s){
    max_w_talii = max_w_talii_s;
    return;
}
void karta::setLeg(bool leg_s){
    legendarna = leg_s;
    return;
}
void karta::setFlavor(QString flavor_s){
    flavor_text = flavor_s;
    return;
}

//jeśli dodane zostaną kart o negatywnym booście trzeba zaaktualizować tą funkcję
//przy dodawaniu kart typu biedna ******* piechota zaaktualizować funkcję
void karta::updateSila(bool pogoda, bool horn, int boost){
    if (pogoda && sila_bazowa > 0){
        sila = (1 + boost) * (1 + horn);
    }
    else {
        sila = (sila_bazowa + boost) * (1 + horn);
    }
    return;
}

unsigned int karta::getID(){
    return id;
}

QString karta::getNazwa(){
    return nazwa;
}

Frakcja karta::getFrakcja(){
    return frakcja;
}

Kategoria karta::getKategoria(){
    return kategoria;
}

unsigned int karta::getSila(){
    return sila;
}

//tu coś z keywordem jak to zrobię

unsigned int karta::getMax(){
    return max_w_talii;
}

bool karta::getLeg(){
    return legendarna;
}

QString karta::getFlavor(){
    return flavor_text;
}
