#ifndef GRA_H
#define GRA_H

#include "player.h"
#include "efekty_pogodowe.h"
#include "card_button.h"
#include "karta.h"

#include <QPushButton>
#include <vector>

enum StanGry {
    Tura1, Tura2, KoniecRundy, KoniecGry, Nierozpoczeta
};

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
    //tą funkcję podepniemy do przycisków

    void globalCardPlayed(karta* karta_g, int nr_gracza);
    //void przerysowaniePlanszy(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent);
    //void gameClear(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza);
    //void zagranoKarte(karta* nowaKarta, std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent);
    //void zagranoKarte(karta* nowaKarta, int nr_gracza);
    //nie wiem czy to nie powinno byc w private i dodatkowa funkcja w publicu,
    //żeby było bardziej akademicko czy coś, ale na razie zostawiam
    //dodałem do tej funkcji że ona od razy wywłuje przeryswanie
    void zagranoKarte(int indeks, int nr_gracza);
    void gameClear();
private:
    player *gracz_1;
    player *gracz_2;
    efekty_pogodowe pogoda;

    StanGry GameState = Nierozpoczeta;

  // void redrawBoard(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza, QWidget* parent);
 //   void clearBoard(std::vector<Card_Button*>& kartyPlansza,QLayout* plansza);
    void clearBoard();
    void redrawBoard();


    std::vector<karta*> daneKartNaPlanszy; //przenosze te dane z mainwindow do gry aby tak jak mówiłeś to był mózg

signals:
    //void dodanieKarty(karta* nowaKarta, gra::RzadPlanszy rzad);
    void nakazRysowaniaKarty(karta* nowaKarta, gra::RzadPlanszy rzad, int indeks, int nr_gr);

    // Rozkaz: "Wyczyść fizycznie ten konkretny rząd/layout z przycisków"
    void nakazCzyszczeniaLayoutu(gra::RzadPlanszy rzad);
};

#endif // GRA_H
