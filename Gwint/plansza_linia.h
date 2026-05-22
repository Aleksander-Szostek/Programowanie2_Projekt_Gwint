#ifndef PLANSZA_LINIA_H
#define PLANSZA_LINIA_H
#include "kontener_kart.h"

class plansza_linia : public kontener_kart
{
public:
    plansza_linia();

    int getPoints();

//    kontener_kart linia;

    void emptyLinia();

private:

    kontener_kart horn;
};

#endif // PLANSZA_LINIA_H