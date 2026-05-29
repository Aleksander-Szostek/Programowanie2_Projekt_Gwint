#ifndef PLAYER_H
#define PLAYER_H
#include "deck.h"
#include "player_hand.h"
#include "plansza_linia.h"
#include "graveyard.h"


enum kontener{talia, reka, linia_melee, linia_ranged, linia_siege, cmentarz, lider};

struct decyzjaRuchu{
    bool pasuje;
    int nr_karty;
};

class player
{
public:
    player();

    
    void getPoints(int return_val[3], bool Pogoda[3]);
    virtual ~player() = default;

    virtual decyzjaRuchu podjecieDecyzji(player* przeciwnik) = 0; //przekazuje wskaźnik do planszy gracza,a by bot mógł sobie policzyć co zagra

    plansza_linia* getMelee();
    plansza_linia* getRanged();
    plansza_linia* getSiege();
    deck* getDeck();
    player_hand* getReka();


    void dobierzKarte();

    karta* zagrajKarte(int nr_w_rece);

    void uzyjLidera();

    void Spasuj(bool reverse = false);
    void ResetPasa();
    void Pasuj();

    bool isPas();

    void startRundy();

    void wyczysc();

    int getPunktyK();
    void setPunktyK(int a);

private:

    int punkty=0;

    deck *Talia;
    player_hand *reka;
    plansza_linia *melee_l;
    plansza_linia *ranged_l;
    plansza_linia *siege_l;
    graveyard *cmentarzysko;

    bool czyPas = false;
};

#endif // PLAYER_H
