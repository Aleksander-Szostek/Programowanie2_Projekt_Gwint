#ifndef KONTENER_KART_H
#define KONTENER_KART_H
#include "karta.h"

class kontener_kart
{
public:
    kontener_kart();

    void add_card_to(karta* dodawana_karta, int pozycja);

    void move_card(int pozycja_startowa, kontener_kart* output_deck_adress, int pozycja_koncowa);

    void delete_card(int pozycja);

    void shulfe_list();

    void sort_list();

    void getKartaFromList(int poz);

protected:

    std::vector<karta*> Ciag_kart;

};

#endif // KONTENER_KART_H