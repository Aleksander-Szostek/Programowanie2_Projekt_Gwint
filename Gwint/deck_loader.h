#ifndef DECK_LOADER_H
#define DECK_LOADER_H
#include "kontener_kart.h"


class deck_loader
{
public:
    deck_loader();

    std::vector<karta*> load_deck(QString fileName);
};

#endif // DECK_LOADER_H
