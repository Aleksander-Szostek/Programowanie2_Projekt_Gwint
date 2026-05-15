#ifndef CARD_LOADER_H
#define CARD_LOADER_H
#include "karta.h"

class card_loader
{
public:
    card_loader();

    void zaladuj_karte(int id, karta* Karta);

    //~card_loader();
};

#endif // CARD_LOADER_H
