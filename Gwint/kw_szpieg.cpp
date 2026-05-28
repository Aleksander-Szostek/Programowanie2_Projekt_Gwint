#include "kw_szpieg.h"

szpieg::szpieg() {}

void szpieg::whenPlayed(RzadPlanszy rzad, int indeks) {
    if (isPlayer1(rzad)) {
        //nakazDobierz(1, 2);
        }
    else
        {
        //nakazDobierz(2, 2);
        }

    //nakazRusz(rzad, indeks, getReverseRzada(rzad));
}

void szpieg::whenKilled(RzadPlanszy rzad, int indeks) {
    return;
    //szpieg umiera jak każdy, ewentualnie zamienia się w stonkę
}


RzadPlanszy szpieg::getReverseRzada(RzadPlanszy rzad) {
    switch (rzad) {

    case P1_Melee:{
        return P2_Melee;
        break;
    }

    case P1_Range:{
        return P2_Range;
        break;
    }

    case P1_Siege:{
        return P2_Siege;
        break;
    }

    case P2_Melee:{
        return P1_Melee;
        break;
    }

    case P2_Range:{
        return P1_Range;
        break;
    }

    case P2_Siege:{
        return P1_Siege;
        break;
    }

    default: {
        qDebug() << "Niewłaściwy typ karty dla szpiega.";
        return Unknown;
    }

    }

}