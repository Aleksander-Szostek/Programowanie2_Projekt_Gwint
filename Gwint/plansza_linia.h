#ifndef PLANSZA_LINIA_H
#define PLANSZA_LINIA_H
#include "kontener_kart.h"

class plansza_linia : public kontener_kart
{
public:
    plansza_linia();

    int getPoints(bool Pogoda);

    void emptyLinia();

    kontener_kart* getHorn();

    bool isCloudy();

    void setCloudy();

private:

    kontener_kart* horn;

    bool getHornBool();

    bool Cloudy();

    bool isHorny();

    void updateSilaBraterstwa(int indeks, bool pogoda, bool horn, int boost);

    int boost = 0;

    void testBoost();
};

#endif // PLANSZA_LINIA_H
