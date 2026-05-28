#ifndef KEYWORD_H
#define KEYWORD_H
#include <vector>
#include <qobject.h>
#include "rzedy_enum.h"
#include <QDebug>

class keyword
{
public:
    keyword();

    virtual void whenPlayed(RzadPlanszy rzad = Unknown, int indeks = 0) = 0;
    virtual void whenKilled(RzadPlanszy rzad = Unknown, int indeks = 0) = 0;

    struct lokacjaKarty {
        RzadPlanszy miejsce;
        int indeks;
    };

    ~keyword();

protected:
    std::vector<int> Karty_cele;
    std::vector<RzadPlanszy> Linie_cele;

    bool isPlayer1(RzadPlanszy rzad);

signals:
    void nakazRusz(RzadPlanszy poz_start, int indeks, RzadPlanszy poz_kon);
    std::vector<lokacjaKarty> nakazSzukaj(RzadPlanszy gdzieSzukac, int ID);
    void nakazGrzybek();
    void nakazDobierz(int nr_gracza, int liczba = 1);

    //wiem że nie mieliśmy jeszcze bardziej przepełniać gra.cpp
    //ale nie wiem jak ten syf zrobić bez przerabiania całego kodu pod to
};

#endif // KEYWORD_H
