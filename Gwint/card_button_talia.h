#ifndef CARD_BUTTON_TALIA_H
#define CARD_BUTTON_TALIA_H

#include "card_button.h"

class Card_Button_Talia : public Card_Button
{
    Q_OBJECT
public:
    explicit Card_Button_Talia(karta* daneKarty, QWidget *parent);
    ~Card_Button_Talia();
private:
    karta* przechowywanaKarta;
};

#endif // CARD_BUTTON_TALIA_H
