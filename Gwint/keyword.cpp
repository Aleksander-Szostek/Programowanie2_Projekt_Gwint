#include "keyword.h"

keyword::keyword() {}

void effekt(){
    return;
};

bool keyword::isPlayer1(RzadPlanszy rzad) {
    if (rzad == P1_Hand ||
        rzad == P1_Melee ||
        rzad == P1_Range ||
        rzad == P1_Siege ||
        rzad == P1_Leader ||
        rzad == P1_Spell)
            return true;

    else
        return false;
}