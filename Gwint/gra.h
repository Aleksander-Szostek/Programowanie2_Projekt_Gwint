#ifndef GRA_H
#define GRA_H
#include "player.h"
#include "efekty_pogodowe.h"

class gra
{
public:
    gra();

    void zainicjalizuj_gre();
    void koniec_rundy();
    void koniec_gry();


private:
    player *gracz_1;
    player *gracz_2;
    efekty_pogodowe pogoda;

};

#endif // GRA_H
