#ifndef BOT_PLAYER_H
#define BOT_PLAYER_H

#include "efekty_pogodowe.h"
#include "player.h"

class bot_player : public player
{
public:
    bot_player();

    decyzjaRuchu podjecieDecyzji(player* przeciwnik) override;

    void setPogodaStol(efekty_pogodowe* p) { aktualnaPogoda = p; }

    std::vector<karta*> pobierzWszyskieKarty(player* p);
private:
    bool czyPasowac(player* przeciwnik);
    int ocenaKarty(karta* k, player* przeciwnik);
    bool czySzpieg(karta* k, player* przeciwnik);
    bool czyPorzoga(karta* k, player* przeciwnik);
    bool czyKukla(karta* k, player* przeciwnik);
    bool czyPogoda(karta* k, player* przeciwnik);
    int liniaDoAgile(karta* k);
    efekty_pogodowe* aktualnaPogoda = nullptr;
};

#endif // BOT_PLAYER_H
