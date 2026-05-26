#include "human_player.h"

human_player::human_player() {}

decyzjaRuchu human_player::podjecieDecyzji(player* przeciwnik) {
    decyzjaRuchu azbest;
    azbest.nr_karty = 0;
    azbest.pasuje = 0;
    return azbest;
}
