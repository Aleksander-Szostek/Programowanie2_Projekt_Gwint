#ifndef GRA_H
#define GRA_H
#include "player.h"
#include "efekty_pogodowe.h"

enum StanGry {
    Tura1, Tura2, KoniecRundy, KoniecGry, Nierozpoczeta
};

class gra
{
public:
    gra();

    void zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2);
    void koniec_rundy();
    void koniec_gry();

    void graczZagrajKarte(int nr_w_rece, int nr_gracza);
    //jeśli zostanie zagrana karta która ma effekt globalny to musi zostać resolvowana w tym obiekcie
    //tą funkcję podepniemy do przycisków

    void globalCardPlayed(karta* karta_g, int nr_gracza);

private:
    player *gracz_1;
    player *gracz_2;
    efekty_pogodowe pogoda;

    StanGry GameState = Nierozpoczeta;

    void redrawBoard();
};

#endif // GRA_H
