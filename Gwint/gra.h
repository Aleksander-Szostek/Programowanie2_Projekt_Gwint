#ifndef GRA_H
#define GRA_H

#include "player.h"
#include "efekty_pogodowe.h"
#include "karta.h"

#include <QPushButton>
#include <QTimer>

#include "stan_gry.h"
#include "rzedy_enum.h"
// enum StanGry {
//     Tura1, Tura2, KoniecRundy, KoniecGry, Nierozpoczeta
// };

class gra : public QObject
{
    Q_OBJECT
public:

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

    void moveCardByEnum(RzadPlanszy rzad_start, RzadPlanszy rzad_end, int ID);
    int findCardByID(RzadPlanszy rzad, int ID);

    kontener_kart* getKontenerByEnum(RzadPlanszy rzad);

    void szpieg(karta* active, int nr_gracza);
    void przyzwij(karta* active, int nr_gracza);
    void linked(karta* active, int nr_gracza);
    void medyk(karta* active, int nr_gracza);
    void rebornDEAD(karta* active, int nr_gracza);
    void porzoga(karta* active, int nr_gracza);
    void pogodaPlay(karta* active, int nr_gracza);
    void horn(karta* active, int nr_gracza);
    void boost(karta* active, int nr_gracza);
    void grzyb(karta* active, int nr_gracza);

signals:
    //void dodanieKarty(karta* nowaKarta, gra::RzadPlanszy rzad);
    void nakazRysowaniaKarty(karta* nowaKarta, RzadPlanszy rzad, int indeks, int nr_gr);

    // Rozkaz: "Wyczyść fizycznie ten konkretny rząd/layout z przycisków"
    void nakazCzyszczeniaLayoutu(RzadPlanszy rzad);

    void nakazAktualizacjiPunkt(int punkty[12]);

    void nakazZmianyStrony(int indeks);

    void nakazShowGS(StanGry GameState, bool p1_pas, bool p2_pas);
};

#endif // GRA_H
