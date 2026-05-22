#ifndef CARD_BUTTON_H
#define CARD_BUTTON_H

#include "karta.h"
#include <QPushButton>

class Card_Button : public QPushButton
{
    Q_OBJECT
public:
    explicit Card_Button(karta* daneKarty, QWidget *parent=nullptr); //przekazuje wskaźnik danych karty

    void refresh(); //do aktualizacji wyglądu karty, np siły po jakiś efektach

    karta* getCardData() {return k_dane;}

    int getIndeks();
private:
    karta* k_dane;

    int indeks = 0;
};

#endif // CARD_BUTTON_H
