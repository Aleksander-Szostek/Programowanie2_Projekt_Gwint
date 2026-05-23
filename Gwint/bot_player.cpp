#include "bot_player.h"
#include <qdebug.h>
#include "karta.h"
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
    int najwyzszy_wynik = -1000;

    for(int i =0; i<getReka()->getDeckSize();++i){ //przechdzi po calej rece bota
        karta* ocenianaKarta = getReka()->getKartaFromList(i);
        int wynik = ocenaKarty(ocenianaKarta,przeciwnik);
        if(wynik> najwyzszy_wynik){
            nr_najlepszej_karty=i;
            najwyzszy_wynik= wynik;
        }
    }
    qDebug()<<"Najlepsza karta do zagrania to: "<<getReka()->getKartaFromList(nr_najlepszej_karty)->getNazwa();
    decyzja.nr_karty=nr_najlepszej_karty;
    return decyzja;
}


bool bot_player::czyPasowac(player* przeciwnik){
    if(getPoints()> przeciwnik->getPoints() && przeciwnik->isPas()){
        return true;
    }
    //if(aktualnyStan == StanGry::){ //aby nie pasował w ostatniej
    //    return false;
    //}
    return false;
}

int bot_player::ocenaKarty(karta* k, player* przeciwnik){ //k aby klasa i parametr tak samo nie nazywały
    return 10;
}
