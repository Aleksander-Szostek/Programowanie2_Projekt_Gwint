#ifndef GRA_H
#define GRA_H

#include "player.h"
#include "efekty_pogodowe.h"
#include "card_button.h"
#include "karta.h"

#include <QPushButton>
#include <vector>
#include <QTimer>

#include "stan_gry.h"
// enum StanGry {
//     Tura1, Tura2, KoniecRundy, KoniecGry, Nierozpoczeta
// };

class gra : public QObject
{
    Q_OBJECT
public:
    enum RzadPlanszy{
        P1_Melee,
        P1_Range,
        P1_Siege,
        P2_Melee,
        P2_Range,
        P2_Siege,
        P1_Spell,
        P2_Spell,
        P1_Leader,
        P2_Leader,
        P1_Hand,
        P2_Hand
    };

    enum class Pkt{
        p1_M = 0,
        p1_R = 1,
        p1_S = 2,
        p2_M = 3,
        p2_R = 4,
        p2_S = 5,

        p1_DS = 6,
        p2_DS = 7,
        p1_HS = 8,
        p2_HS = 9,

        p1_GS = 10,
        p2_GS = 11
    };

    gra();

    void zainicjalizuj_gre(QString nazwa_talii_1, QString nazwa_talii_2);
    void koniec_rundy();
    void koniec_gry();
    void dobierzKarte(int nr_gracza, int n = 1);
    void graczZagrajKarte(int nr_w_rece, int nr_gracza);

    //jeśli zostanie zagrana karta która ma effekt globalny to musi zostać resolvowana w tym obiekcie
    void globalCardPlayed(karta* karta_g, int nr_gracza);
    void zagranoKarte(int indeks, int nr_gracza);
    void gameClear();

    void tura_bota();
    void wybranoKarte(RzadPlanszy lokacja, int indeks);
    void countPoints();
    void graczPas(int nr_gr);
    StanGry getGameState();
    int getNrRundy();


private:
    player *gracz_1;
    player *gracz_2;
    efekty_pogodowe pogoda;

    int p1_pkt = 0;
    int p2_pkt = 0;

    int p1_gamescore = 0;
    int p2_gamescore = 0;

    StanGry GameState = Nierozpoczeta;

    void clearBoard();
    void redrawBoard();

    void clearPlansza();

    int nr_rundy = 0;

signals:
    //void dodanieKarty(karta* nowaKarta, gra::RzadPlanszy rzad);
    void nakazRysowaniaKarty(karta* nowaKarta, gra::RzadPlanszy rzad, int indeks, int nr_gr);

    // Rozkaz: "Wyczyść fizycznie ten konkretny rząd/layout z przycisków"
    void nakazCzyszczeniaLayoutu(gra::RzadPlanszy rzad);

    void nakazAktualizacjiPunkt(int punkty[12]);

    void nakazZmianyStrony(int indeks);

    void nakazShowGS(StanGry GameState, bool p1_pas, bool p2_pas);
};

#endif // GRA_H
