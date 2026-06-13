#include "card_button_talia.h"
#include "i_constant_valuse.h"

Card_Button_Talia::Card_Button_Talia(karta* daneKarty, QWidget *parent): Card_Button(daneKarty, parent){
    //setFixedSize(wysokosc_karty/proporcje_karty,wysokosc_karty); // rozmiar karty
    int h = 80;
    setFixedSize(h,h*proporcje_karty);
}
