#ifndef RZEDY_ENUM_H
#define RZEDY_ENUM_H
#include "karta.h"

enum RzadPlanszy{
    Unknown,

    P1_Melee,
    P1_Range,
    P1_Siege,
    P2_Melee,
    P2_Range,
    P2_Siege,

    P1_Spell,
    P2_Spell,

    P1_Leader,
    P2_Leader,

    P1_Hand,
    P2_Hand,

    P1_Deck,
    P2_Deck,

    P1_Graveyard,
    P2_Graveyard,

    P1_Limbo,
    P2_Limbo,

    Weather,

    P1_Melee_Horn,
    P1_Range_Horn,
    P1_Siege_Horn,
    P2_Melee_Horn,
    P2_Range_Horn,
    P2_Siege_Horn
};

enum class Pkt{
    p1_M = 0,
    p1_R = 1,
    p1_S = 2,
    p2_M = 3,
    p2_R = 4,
    p2_S = 5,

    p1_DS = 6,
    p2_DS = 7,
    p1_HS = 8,
    p2_HS = 9,

    p1_GS = 10,
    p2_GS = 11
};

struct nakaz {

};


class rzedy_enum
{
public:
    rzedy_enum();

    bool isPlayer1(RzadPlanszy rzad);
    RzadPlanszy reverseRzad(RzadPlanszy rzad);

    RzadPlanszy convertTypToRzad(Kategoria typ, int nr_gracza);

};

#endif // RZEDY_ENUM_H
