#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include "player.h"

class bot_player : public player
{
public:
    bot_player();

    decyzjaRuchu podjecieDecyzji(player* przeciwnik) override;
private:
    bool czyPasowac(player* przeciwnik);
    int ocenaKarty(karta* k, player* przeciwnik);
};

#endif // BOT_PLAYER_H
