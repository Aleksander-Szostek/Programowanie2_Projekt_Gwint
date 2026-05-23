#ifndef PLANSZA_LINIA_H
#define PLANSZA_LINIA_H
#include "kontener_kart.h"

class plansza_linia : public kontener_kart
{
public:
    plansza_linia();

    int getPoints(bool Pogoda);

//    kontener_kart linia;

    //nie wiem do czego chciałeś używać ale zakładam że do czyszczenia linii więc tak użyję w razie co daj mój kod do jakiejś funkcji typu czysczeniLini czy cos w tym stylu
    void emptyLinia();

    karta* getHorn();

private:

    kontener_kart horn;

    bool getHornBool();
};

#endif // PLANSZA_LINIA_H
