#include "bot_player.h"
#include <qdebug.h>
#include "efekty_pogodowe.h"
#include "karta.h"
#include <cstdlib>
#include <cmath>

bot_player::bot_player() {}

decyzjaRuchu bot_player::podjecieDecyzji(player* przeciwnik){
    decyzjaRuchu decyzja;

    if(czyPasowac(przeciwnik) == true){
        decyzja.pasuje = true;
        return decyzja;
    }

    decyzja.pasuje = false;
    int nr_najlepszej_karty = 0;
    int waga_karty = 1000;

    bool pogoda[3] = {false, false, false};
    if (aktualnaPogoda != nullptr) {
        pogoda[0] = aktualnaPogoda->isMeleePogoda();
        pogoda[1] = aktualnaPogoda->isRangePogoda();
        pogoda[2] = aktualnaPogoda->isSiegePogoda();
    }

    int suma_przeciwnika = przeciwnik->getSumaPunktow(pogoda);

    if(suma_przeciwnika == 0){
        int indeks_min = 0;
        int najszłabsza = 10000;
        for(int i = 0; i < getReka()->getDeckSize(); ++i){
            karta* ocenianaKarta = getReka()->getKartaFromList(i);
            if(ocenianaKarta->getSila() < najszłabsza && ocenianaKarta->getKeyword()!=Szpieg &&ocenianaKarta->getKeyword()!=Pogoda && ocenianaKarta->getKeyword()!=Grzyb
                                                           &&ocenianaKarta->getKeyword()!=Porzoga&& ocenianaKarta->getKeyword()!=Kukla){
                najszłabsza = getReka()->getKartaFromList(i)->getSila();
                indeks_min = i;
            }
        }
        decyzja.nr_karty = indeks_min;
        return decyzja;
    }

    for(int i = 0; i < getReka()->getDeckSize(); ++i){
        karta* ocenianaKarta = getReka()->getKartaFromList(i);
        int obecna_waga = ocenaKarty(ocenianaKarta, przeciwnik);
        if(obecna_waga < waga_karty){
            nr_najlepszej_karty = i;
            waga_karty = obecna_waga;
        }
    }
    qDebug() << "Bot zagral: " << getReka()->getKartaFromList(nr_najlepszej_karty)->getNazwa();
    decyzja.nr_karty = nr_najlepszej_karty;
    return decyzja;
}

bool bot_player::czyPasowac(player* przeciwnik){
    bool pogoda[3] = {false, false, false};
    if (aktualnaPogoda != nullptr) {
        pogoda[0] = aktualnaPogoda->isMeleePogoda();
        pogoda[1] = aktualnaPogoda->isRangePogoda();
        pogoda[2] = aktualnaPogoda->isSiegePogoda();
    }

    int suma_przeciwnika = przeciwnik->getSumaPunktow(pogoda);

    int suma_bota = getSumaPunktow(pogoda);

    if(suma_bota > suma_przeciwnika && przeciwnik->isPas()){
        return true;
    }

    if(getReka()->getDeckSize() == 0){
        return true;
    }

    if(getPunktyK() == 1 && przeciwnik->getPunktyK() == 1){
        return false;
    }

    return false;
}

int bot_player::ocenaKarty(karta* k, player* przeciwnik){

    bool pogoda[3] = {false, false, false};
    if (aktualnaPogoda != nullptr) {
        pogoda[0] = aktualnaPogoda->isMeleePogoda();
        pogoda[1] = aktualnaPogoda->isRangePogoda();
        pogoda[2] = aktualnaPogoda->isSiegePogoda();
    }
    if(k->getKeyword()==Pogoda){
        if(czyPogoda(k,przeciwnik)==true){
            return -100;
        }
        else{
            return 1000;
        }
    }
    if(k->getKeyword()==Szpieg){
        if(czySzpieg(k,przeciwnik)){
            return -100;
        }
        else{
            return 1000;
        }
    }
    if(k->getKeyword()==Porzoga){
        if(czyPorzoga(k,przeciwnik)){
            return -100;
        }
        else{
            return 1000;
        }
    }
    if(k->getKeyword()==Kukla){
        if(czyKukla(k,przeciwnik)){
            return -100;
        }
        else{
            return 1000;
        }
    }
    if(k->getKeyword()==Grzyb){
        if(czyGrzybiarz(k, przeciwnik)){
            return -100;
        }
        else{
            return 1000;
        }
    }
    int suma_przeciwnika = przeciwnik->getSumaPunktow(pogoda);

    int suma_bota = getSumaPunktow(pogoda);

    int sila_k = static_cast<int>(k->getSila());
    int wynik_po_ruchu = suma_bota + sila_k;

    if(przeciwnik->isPas()){
        if(wynik_po_ruchu > suma_przeciwnika){
            return wynik_po_ruchu - suma_przeciwnika;
        }
        else{
            return 100 + sila_k;
        }
    }
    else{
        if(wynik_po_ruchu > suma_przeciwnika){
            return wynik_po_ruchu - suma_przeciwnika;
        }
        else{
            return 200 - sila_k;
        }
    }
}


bool bot_player::czyPogoda(karta* k, player* przeciwnik){
    if (aktualnaPogoda == nullptr) return false;

    std::vector<int> celeKarty = k->getCele();
    int targetowanyRzad = 0;

    for (int cel : celeKarty) {
        if (cel == -1 || cel == -2 || cel == -3) {
            targetowanyRzad = cel;
            break;
        }
    }
    if(targetowanyRzad == 0){
        return false;
    }

    bool pogoda[3];
    pogoda[0] = aktualnaPogoda->isMeleePogoda();
    pogoda[1] = aktualnaPogoda->isRangePogoda();
    pogoda[2] = aktualnaPogoda->isSiegePogoda();

    if(targetowanyRzad == -1 && pogoda[0] == true) return false;
    else if(targetowanyRzad == -2 && pogoda[1] == true) return false;
    else if(targetowanyRzad == -3 && pogoda[2] == true) return false;

    int starePunktyPrzeciwnika[3];
    przeciwnik->getPoints(starePunktyPrzeciwnika, pogoda);

    int indeksRzedu = std::abs(targetowanyRzad) - 1;
    pogoda[indeksRzedu] = true;

    int nowePunktyPrzeciwnika[3];
    przeciwnik->getPoints(nowePunktyPrzeciwnika, pogoda);

    int nowePunktyBota[3];
    getPoints(nowePunktyBota, pogoda);

    int strataPrzeciwnika = starePunktyPrzeciwnika[indeksRzedu] - nowePunktyPrzeciwnika[indeksRzedu];
    int strataBota = starePunktyPrzeciwnika[indeksRzedu] - nowePunktyBota[indeksRzedu];

    int Zysk = strataPrzeciwnika - strataBota;

    if (Zysk >= 7) {
        return true;
    }

    return false;
}

bool bot_player::czySzpieg(karta* k, player* przeciwnik) {
    bool pogoda[3] = {false, false, false};
    if (aktualnaPogoda != nullptr) {
        pogoda[0] = aktualnaPogoda->isMeleePogoda();
        pogoda[1] = aktualnaPogoda->isRangePogoda();
        pogoda[2] = aktualnaPogoda->isSiegePogoda();
    }
    int punkty_przeciwnika= przeciwnik->getSumaPunktow(pogoda);

    int punkty_bota=getSumaPunktow(pogoda);
    if(przeciwnik->isPas()==true && punkty_przeciwnika+k->getSila()<punkty_bota){
        return true;
    }

    if(przeciwnik->getPunktyK()==1 || getPunktyK()==1){
        return false;
    }
    if(przeciwnik->getPunktyK()==0){
        if(punkty_przeciwnika+k->getSila()<punkty_bota || punkty_przeciwnika>punkty_bota+10){
            return true;
        }
    }
    return false;

}
std::vector<karta*> bot_player::pobierzWszyskieKarty(player* p){
    std::vector<karta*> jednostki;
    kontener_kart* linie[] = { p->getMelee(), p->getRanged(), p->getSiege()};

    for (auto* linia : linie) {
        for (int i = 0; i < linia->getDeckSize(); i++) {
            jednostki.push_back(linia->getKartaFromList(i));
        }
    }
    return jednostki;
}
bool bot_player::czyPorzoga(karta* k, player* przeciwnik) {

    std::vector<karta*> kartyBota = pobierzWszyskieKarty(this);
    std::vector<karta*> kartyPrzeciwnika = pobierzWszyskieKarty(przeciwnik);

    int maxSila = 0;

    for(auto* i : kartyBota){
        if(i->getSila() > maxSila && i->getLeg()==false){
            maxSila = i->getSila();
        }
    }
    for(auto* j : kartyPrzeciwnika){
        if(j->getSila() > maxSila && j->getLeg()==false){
            maxSila = j->getSila();
        }
    }
    if (maxSila < 5){//nie maq co marnować porzogi na słabe karty
        return false;
    }
    //sprawdza czy gracz ma najsilniejsza
    bool przeciwnikMaNajsilniejszą = false;
    for (auto* i : kartyPrzeciwnika) {
        if (i->getSila() == maxSila) {
            przeciwnikMaNajsilniejszą = true;
            break;
        }
    }
    //sprawdza czy bot ma najsilniejsza
    bool botMaNajsilniejszą = false;
    for (auto* j : kartyBota) {
        if (j->getSila() == maxSila) {
            botMaNajsilniejszą = true;
            break;
        }
    }

    if(przeciwnikMaNajsilniejszą==true && botMaNajsilniejszą==false){
        return true;
    }
    else{
        return false;
    }


}


bool bot_player::czyKukla(karta* k, player* przeciwnik) {
    std::vector<karta*> kartyBota = pobierzWszyskieKarty(this);
    if(kartyBota.empty()) return false;


    for (auto* j : kartyBota) {
        if (j->getKeyword() == Szpieg) {
            return true;
        }
    }


    int maxSila = 0;
    bool znalezionoCel = false;
    karta* naj;
    for (auto* i : kartyBota) {
        if (i->getLeg() != true && i->getKategoria() != Spell) {
            if (i->getSila() > maxSila) {
                maxSila = i->getSila();
                naj=i;
                znalezionoCel = true;
            }
        }
    }
    qDebug()<<"Bot znalazł: "<<naj->getNazwa();
    if (znalezionoCel && maxSila > 6) {
        return true;
    }

    return false;
}
bool bot_player::czyGrzybiarz(karta* k, player* przeciwnik) {
    std::vector<karta*> kartyBota = pobierzWszyskieKarty(this);

    for (auto* i : kartyBota) {

        if (i->getKeyword() == Morph) {
            return true;
        }
    }

    return false;
}
