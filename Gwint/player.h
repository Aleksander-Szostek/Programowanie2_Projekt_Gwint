#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "player_hand.h"
#include "plansza_linia.h"
#include "graveyard.h"

enum kontener{talia, reka, linia_melee, linia_ranged, linia_siege, cmentarz, lider};

class player
{
public:
    player();

    int getPoints();
    karta* getKontener(kontener typKontenera);

    void dobierzKarte();

    void zagrajKarte(int nr_w_rece);

    void uzyjLidera();

    void Spasuj();

    bool isPas();

    void startRundy();

private:
    deck *Talia;
    player_hand *reka;
    plansza_linia *melee_l;
    plansza_linia *ranged_l;
    plansza_linia *siege_l;
    graveyard *cmentarzysko;

    bool czyPas;
};

#endif // PLAYER_H
