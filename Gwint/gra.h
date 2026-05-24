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

private:
    player *gracz_1;
    player *gracz_2;
    efekty_pogodowe pogoda;

    int p1_pkt = 0;
    int p2_pkt = 0;

    int p1_gamescore = 0;
    int p2_gamescore = 0;

    StanGry GameState = Nierozpoczeta;

  // void redrawBoard(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent);
 //   void clearBoard(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza);
    void clearBoard();
    void redrawBoard();

    void clearPlansza();


    std::vector<karta*> daneKartNaPlanszy; //przenosze te dane z mainwindow do gry aby tak jak mówiłeś to był mózg

signals:
    //void dodanieKarty(karta* nowaKarta, gra::RzadPlanszy rzad);
    void nakazRysowaniaKarty(karta* nowaKarta, gra::RzadPlanszy rzad, int indeks, int nr_gr);

    // Rozkaz: "Wyczyść fizycznie ten konkretny rząd/layout z przycisków"
    void nakazCzyszczeniaLayoutu(gra::RzadPlanszy rzad);

    void nakazAktualizacjiPunkt(int punkty[12]);
};

#endif // GRA_H
