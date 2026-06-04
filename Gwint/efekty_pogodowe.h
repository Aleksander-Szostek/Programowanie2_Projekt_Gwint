#ifndef EFEKTY_POGODOWE_H
#define EFEKTY_POGODOWE_H

#include "kontener_kart.h"

class efekty_pogodowe : public kontener_kart
{
public:
    efekty_pogodowe();

    bool isMeleePogoda();
    bool isRangePogoda();
    bool isSiegePogoda();

    void wyczysc();

private:
    bool scanLine(int nr_linii);
};

#endif // EFEKTY_POGODOWE_H
