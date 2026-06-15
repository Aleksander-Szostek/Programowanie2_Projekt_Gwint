#include "card_button_talia.h"
#include "i_constant_valuse.h"

Card_Button_Talia::Card_Button_Talia(karta* daneKarty, QWidget *parent): Card_Button(daneKarty, parent){

    int h = 80;
    setFixedSize(h,h*proporcje_karty);

    przechowywanaKarta = daneKarty;
}
Card_Button_Talia::~Card_Button_Talia(){
    if (przechowywanaKarta != nullptr) {
        delete przechowywanaKarta;
        przechowywanaKarta = nullptr;
    }
}
