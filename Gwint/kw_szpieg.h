#ifndef KW_SZPIEG_H
#define KW_SZPIEG_H

#include "keyword.h"

class szpieg : public keyword
{
public:
    szpieg();

    void whenPlayed(RzadPlanszy rzad = Unknown, int indeks = 0) override;
    void whenKilled(RzadPlanszy rzad = Unknown, int indeks = 0) override;
private:
    RzadPlanszy getReverseRzada(RzadPlanszy rzad);
};

#endif // KW_SZPIEG_H
