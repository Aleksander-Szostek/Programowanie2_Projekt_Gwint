#include "card_button.h"

Card_Button::Card_Button(karta* daneKarty, QWidget *parent) : QPushButton(parent), k_dane(daneKarty)
{
    setFixedSize(130,180); // rozmiar karty
}
void Card_Button::refresh(){
    if(!k_dane)
        return;
    QString nazwa = k_dane->getNazwa();
    int sila = k_dane->getSila();
    bool isLeg = k_dane->getLeg();
    //na razie to zostawiam, potem możemy zmienić na jakas grafikę
    QString borderStyle;
    if(isLeg==true){
        borderStyle = "#91873a";
    }else{
        borderStyle = "#2c3e50";
    }
    QString style = QString(
                        "QPushButton {"
                        "  background-color: %1;"
                        "  color: white;"
                        "  border: 2px solid black;"
                        "  border-radius: 5px;"
                        "}"
                        ).arg(borderStyle);

    this->setStyleSheet(style);
    this->setText(k_dane->getNazwa() + "\nSiła: " + QString::number(k_dane->getSila()));
}
