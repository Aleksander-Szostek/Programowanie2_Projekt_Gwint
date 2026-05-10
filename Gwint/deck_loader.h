#ifndef DECK_LOADER_H
#define DECK_LOADER_H
#include "kontener_kart.h"


class deck_loader
{
public:
    deck_loader();

    kontener_kart::Lista_kart load_deck(QString deck_file_name);
};

#endif // DECK_LOADER_H
