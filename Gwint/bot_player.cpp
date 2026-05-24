#include "bot_player.h"
#include <qdebug.h>
#include "karta.h"
#include <cstdlib>



bot_player::bot_player() {}

decyzjaRuchu bot_player::podjecieDecyzji(player* przeciwnik){

    decyzjaRuchu decyzja;
    //bot sprawdza czy opłaca mu się pasować
    if(czyPasowac(przeciwnik)==true){
        decyzja.pasuje=true;
        return decyzja;
    }
    //jeśli nie to szuka najlepszej karty do zagrania
    decyzja.pasuje=false;
    int nr_najlepszej_karty = 0;
    int najmniejszy_wynik = 1000;
    //jak bot zagrywa pierwszy losuje karte


    int punkty_przeciwnika[3];
    bool pogoda[3] = {false,false,false};
    przeciwnik->getPoints(punkty_przeciwnika,pogoda);
    int suma_przeciwnika = punkty_przeciwnika[0]+punkty_przeciwnika[1] + punkty_przeciwnika[2];
    if(suma_przeciwnika==0){
        int liczba_kart=getReka()->getDeckSize();
        decyzja.nr_karty = rand()%(liczba_kart);
        return decyzja;

    }


    for(int i =0; i<getReka()->getDeckSize();++i){ //przechdzi po calej rece bota
        karta* ocenianaKarta = getReka()->getKartaFromList(i);
        int wynik = ocenaKarty(ocenianaKarta,przeciwnik);
        if(wynik< najmniejszy_wynik){
            nr_najlepszej_karty=i;
            najmniejszy_wynik= wynik;
        }
    }
    qDebug()<<"Najlepsza karta do zagrania to: "<<getReka()->getKartaFromList(nr_najlepszej_karty)->getNazwa();
    decyzja.nr_karty=nr_najlepszej_karty;
    return decyzja;
}


bool bot_player::czyPasowac(player* przeciwnik){
    int punkty_przeciwnika[3];
    bool pogoda[3] = {false,false,false};
    przeciwnik->getPoints(punkty_przeciwnika,pogoda);
    int suma_przeciwnika = punkty_przeciwnika[0]+punkty_przeciwnika[1] + punkty_przeciwnika[2];
    int punkty_bota[3];
    getPoints(punkty_bota,pogoda);
    int suma_bota =punkty_bota[0]+punkty_bota[1] +punkty_bota[2];

    if(suma_bota>suma_przeciwnika && przeciwnik->isPas()){
        return true;
    }
    // if(){ //aby nie pasował w ostatniej
    //    return false;
    // }
    return false;
}

int bot_player::ocenaKarty(karta* k, player* przeciwnik){ //k aby klasa i parametr tak samo nie nazywały
    int punkty_przeciwnika[3];
    bool pogoda[3] = {false,false,false};
    przeciwnik->getPoints(punkty_przeciwnika,pogoda);
    int suma_przeciwnika = punkty_przeciwnika[0]+punkty_przeciwnika[1] + punkty_przeciwnika[2];

    int punkty_bota[3];
    getPoints(punkty_bota,pogoda);
    int suma_bota =
        punkty_bota[0] +
        punkty_bota[1] +
        punkty_bota[2];


    int sila_k = static_cast<int>(k->getSila());

    int wynik_po_ruchu = suma_bota+sila_k;

    if(wynik_po_ruchu>suma_przeciwnika){
        return wynik_po_ruchu-suma_przeciwnika;
    }
    return 1000;

}
