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
        frakcja = Frakcja::Niflgard;
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
void karta::setKeyword(QString efekt_s){
    if (efekt_s == "")
        keyword = Brak;
    else if (efekt_s == "SPY")
        keyword = Szpieg;
    else if (efekt_s == "SUMMON")
        keyword = Przyzwij;
    else if (efekt_s == "LINKED")
        keyword = Linked;
    else if (efekt_s == "REBIRTH")
        keyword = Reborn;
    else if (efekt_s == "MEDIC")
        keyword = Medyk;
    else if (efekt_s == "WEATHER")
        keyword = Pogoda;
    else if (efekt_s == "SCORCH")
        keyword = Porzoga;
    else if (efekt_s == "HORN")
        keyword = Horn;
    else if (efekt_s == "BOOST")
        keyword = Boost;
    else if (efekt_s == "MORPH")
        keyword = Morph;
    else if (efekt_s == "MUSHROOM")
        keyword = Grzyb;
    else
        keyword = Brak;
    return;

}
void karta::setCele(QString cele_s){
    qDebug() << "Wywołano setCele";
    if (cele_s == "") {
        qDebug() << "Brak celi";
        return;
    }

    QStringList dane = cele_s.split(' ');

    //dałem celom będących liniami indeksy negatywne żeby zapisać w 1 liście
    //żeby to samo można był używać do efektów targetujących karty jak i linie
    //  (-1) - MELEE
    //  (-2) - RANGED
    //  (-3) - SIEGE

    for (int i = 0 ; i < dane.size() ; i++)
    {
        qDebug() << "Zapisywanie celu: " + dane[i];
        if (dane[i] == "MELEE")
            cele.push_back(-1);
        else if (dane[i] == "RANGED")
            cele.push_back(-2);
        else if (dane[i] == "SIEGE")
            cele.push_back(-3);
        else {
            qDebug() << "Zapisywanie tego";
            int ID = dane[i].toInt(nullptr, 10);
            cele.push_back(ID);
            //dane[i].toInt(nullptr, 10)
            qDebug() << "Zapisało";
        }
    }

    qDebug() << "Koniec setCele";
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
//i gracza też zmodyfikować
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

unsigned int karta::getMax(){
    return max_w_talii;
}

bool karta::getLeg(){
    return legendarna;
}

QString karta::getFlavor(){
    return flavor_text;
}

Efekt karta::getKeyword(){
    return keyword;
}

std::vector<int> karta::getCele(){
    return cele;
}