#ifndef DECK_SAVER_H
#define DECK_SAVER_H
#include "deck.h"

class deck_saver
{
public:
    deck_saver();

    void save_deck(deck& talia_do_zapisania, QString deck_file_name);
};

#endif // DECK_SAVER_H
