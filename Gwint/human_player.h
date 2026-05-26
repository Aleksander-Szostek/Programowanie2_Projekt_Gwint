#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

#include "player.h"

class human_player : public player
{
public:
    human_player();

    decyzjaRuchu podjecieDecyzji(player* przeciwnik) override;
};

#endif // HUMAN_PLAYER_H
