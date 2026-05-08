#ifndef CARD_LOADER_H
#define CARD_LOADER_H
#include "kontener_kart.h"

class card_loader
{
public:
    card_loader();
//    void wsadz_karte(kontener_kart *directory, int id, int pozycja);
//private:


    karta::Card zaladuj_karte(int id);

    //~card_loader();
};

#endif // CARD_LOADER_H
