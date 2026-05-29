#ifndef KW_SZPIEG_H
#define KW_SZPIEG_H

#include "keyword.h"

class szpieg : public keyword
{
public:
    szpieg();

    void whenPlayed() override;
    void whenKilled() override;
private:
    RzadPlanszy getReverseRzad(RzadPlanszy rzad);
};

#endif // KW_SZPIEG_H
