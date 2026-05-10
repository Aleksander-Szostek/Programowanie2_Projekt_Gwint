#ifndef DECK_SAVER_H
#define DECK_SAVER_H
#include "kontener_kart.h"

class deck_saver
{
public:
    deck_saver();

    void save_deck(kontener_kart::Lista_kart talia,QString deck_file_name);
};

#endif // DECK_SAVER_H
