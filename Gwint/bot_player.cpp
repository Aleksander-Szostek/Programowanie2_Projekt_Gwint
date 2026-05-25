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
    int waga_karty = 1000;
    //jak bot zagrywa pierwszy losuje karte


    int punkty_przeciwnika[3];
    bool pogoda[3] = {false,false,false};
    przeciwnik->getPoints(punkty_przeciwnika,pogoda);
    int suma_przeciwnika = punkty_przeciwnika[0]+punkty_przeciwnika[1] + punkty_przeciwnika[2];


    //na start bot zagrywa najslabsz karte
    if(suma_przeciwnika==0){
        //int liczba_kart=getReka()->getDeckSize();
        //decyzja.nr_karty = rand()%(liczba_kart);
        int indeks_min = 0;
        int najszłabsza = 10000;
        for(int i=0;i<getReka()->getDeckSize();++i){
            if(getReka()->getKartaFromList(i)->getSila()<najszłabsza){
                najszłabsza=getReka()->getKartaFromList(i)->getSila();
                indeks_min=i;
            }
        }
        decyzja.nr_karty=indeks_min;
        return decyzja;
    }


    for(int i =0; i<getReka()->getDeckSize();++i){ //przechdzi po calej rece bota
        karta* ocenianaKarta = getReka()->getKartaFromList(i);
        int obecna_waga = ocenaKarty(ocenianaKarta,przeciwnik);
        if(obecna_waga< waga_karty){
            nr_najlepszej_karty=i;
            waga_karty= obecna_waga;
        }
    }
    qDebug()<<"Bot zagral: "<<getReka()->getKartaFromList(nr_najlepszej_karty)->getNazwa();
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

    if(getReka()->getDeckSize()==0){
        return true;
    }

    //bot nie pasuje w ostatniej rundzie
    if(getPunktyK()==1 && przeciwnik->getPunktyK()==1){
        return false;
    }



    return false;
}

int bot_player::ocenaKarty(karta* k, player* przeciwnik){ //k aby klasa i parametr tak samo nie nazywały
    int punkty_przeciwnika[3];
    bool pogoda[3] = {false,false,false};
    przeciwnik->getPoints(punkty_przeciwnika,pogoda);
    int suma_przeciwnika = punkty_przeciwnika[0]+punkty_przeciwnika[1] + punkty_przeciwnika[2];

    int punkty_bota[3];
    getPoints(punkty_bota,pogoda);
    int suma_bota =punkty_bota[0] +punkty_bota[1] +punkty_bota[2];


    int sila_k = static_cast<int>(k->getSila());

    int wynik_po_ruchu = suma_bota+sila_k;

    // if(wynik_po_ruchu>suma_przeciwnika){
    //     return wynik_po_ruchu-suma_przeciwnika;
    // }
    //aby zagrywał minimalne do przebicia
    if(przeciwnik->isPas()){
        if(wynik_po_ruchu>suma_przeciwnika){
            return wynik_po_ruchu-suma_przeciwnika;
        }
        else{
            return 100 +sila_k;
        }
    }
    else{
        if(wynik_po_ruchu>suma_przeciwnika){
            return wynik_po_ruchu-suma_przeciwnika;
        }
        else{
            return 200 - sila_k;
        }
    }
}
