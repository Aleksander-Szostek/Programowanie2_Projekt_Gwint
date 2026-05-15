#ifndef KONTENER_KART_H
#define KONTENER_KART_H
#include "karta.h"

class kontener_kart
{
public:
    kontener_kart();

    void add_card_to(karta* dodawana_karta, int pozycja);

    void move_card(int poz_start, kontener_kart *output_list);

    void delete_card(int pozycja);

    void shulfe_list();

    void sort_list();

    void getKartaFromList(int poz);

protected:

    std::vector<karta*> Ciag_kart;

    virtual const bool isDeck() = 0;    //jeśli kontenery nie działają to trzeba to zmienić
                                        //robię z tym gambling bo nie chce mi się myśleć
};

#endif // KONTENER_KART_H