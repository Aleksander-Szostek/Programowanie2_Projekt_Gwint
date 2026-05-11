#ifndef DECK_LOADER_H
#define DECK_LOADER_H
#include "kontener_kart.h"


class deck_loader
{
public:
    deck_loader();

    void load_deck(kontener_kart &talia_do_wczytania, QString fileName);
};

#endif // DECK_LOADER_H
