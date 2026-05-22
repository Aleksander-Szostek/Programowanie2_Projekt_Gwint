#ifndef KONTENER_KART_H
#define KONTENER_KART_H
#include "karta.h"

class kontener_kart
{
public:
    kontener_kart();

    void add_card_to(karta* dodawana_karta, int pozycja);

    void move_card(int poz_start, kontener_kart *output_list);

    karta* getKartaFromList(int poz);

    int getDeckSize();

    void shulfe_list();

    void sort_list();

    void delete_card(int pozycja);

protected:

    std::vector<karta*> Ciag_kart;

    bool isDeck = false;

private:

//    void delete_card(int pozycja);
};

#endif // KONTENER_KART_H