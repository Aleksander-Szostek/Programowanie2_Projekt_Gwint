#ifndef KONTENER_KART_H
#define KONTENER_KART_H
#include "karta.h"

class kontener_kart
{
public:
    kontener_kart();

    struct Lista_kart
    {
        std::vector<karta::Card> Ciag_kart;
    };

    void add_card_to(kontener_kart::Lista_kart &deck_adress, karta::Card dodawana_karta, int pozycja);

    void move_card(kontener_kart::Lista_kart &input_deck_adress, int pozycja_startowa, kontener_kart::Lista_kart &output_deck_adress, int pozycja_koncowa);

    void delete_card(kontener_kart::Lista_kart &deck_adress, int pozycja);

    void shulfe_deck(kontener_kart::Lista_kart &deck_adress);

};

#endif // KONTENER_KART_H