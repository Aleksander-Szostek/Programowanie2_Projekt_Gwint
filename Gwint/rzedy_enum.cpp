#include "rzedy_enum.h"

rzedy_enum::rzedy_enum() {}

bool rzedy_enum::isPlayer1(RzadPlanszy rzad){
    if (rzad == P1_Melee ||
        rzad == P1_Range ||
        rzad == P1_Siege ||
        rzad == P1_Hand ||
        rzad == P1_Deck ||
        rzad == P1_Spell ||
        rzad == P1_Leader ||
        rzad == P1_Graveyard ||
        rzad == P1_Limbo)
        return true;
    else
        return false;
}

RzadPlanszy rzedy_enum::reverseRzad(RzadPlanszy rzad) {
    RzadPlanszy reverse = Unknown;

    switch (rzad){
        case P1_Melee: {
            reverse = P2_Melee;
            break;
        }
        case P1_Range: {
            reverse = P2_Range;
            break;
        }
        case P1_Siege: {
            reverse = P2_Siege;
            break;
        }
        case P2_Melee: {
            reverse = P1_Melee;
            break;
        }
        case P2_Range: {
            reverse = P1_Range;
            break;
        }
        case P2_Siege: {
            reverse = P1_Siege;
            break;
        }
        case P1_Spell: {
            reverse = P2_Spell;
            break;
        }
        case P2_Spell: {
            reverse = P1_Spell;
            break;
        }
        case P1_Leader: {
            reverse = P2_Leader;
            break;
        }
        case P2_Leader: {
            reverse = P1_Leader;
            break;
        }
        case P1_Hand: {
            reverse = P2_Hand;
            break;
        }
        case P2_Hand: {
            reverse = P1_Hand;
            break;
        }
        case P1_Deck: {
            reverse = P2_Deck;
            break;
        }
        case P2_Deck: {
            reverse = P1_Deck;
            break;
        }
        case P1_Graveyard: {
            reverse = P2_Graveyard;
            break;
        }
        case P2_Graveyard: {
            reverse = P1_Graveyard;
            break;
        }
        default:
            break;
    }

    return reverse;
}

RzadPlanszy rzedy_enum::convertTypToRzad(Kategoria typ, int nr_gracza) {
    RzadPlanszy konwersja = Unknown;

    switch (typ) {
        case Spell: {
            if (nr_gracza == 1)
                konwersja = P1_Spell;
            else
                konwersja = P2_Spell;
            break;
        }
        case Melee: {
            if (nr_gracza == 1)
                konwersja = P1_Melee;
            else
                konwersja = P2_Melee;
            break;
        }
        case Siege: {
            if (nr_gracza == 1)
                konwersja = P1_Siege;
            else
                konwersja = P2_Siege;
            break;
        }
        case Ranged: {
            if (nr_gracza == 1)
                konwersja = P1_Range;
            else
                konwersja = P2_Range;
            break;
        }
        case Leader: {
            if (nr_gracza == 1)
                konwersja = P1_Leader;
            else
                konwersja = P2_Leader;
            break;
        }
        default:
            break;

    }

    return konwersja;
}