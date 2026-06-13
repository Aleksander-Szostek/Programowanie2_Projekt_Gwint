#include "card_button.h"
#include "i_constant_valuse.h"
Card_Button::Card_Button(karta* daneKarty, QWidget *parent) : QPushButton(parent), k_dane(daneKarty)
{
    setFixedSize(wysokosc_karty/proporcje_karty,wysokosc_karty); // rozmiar karty
}
void Card_Button::refresh(){
    if(!k_dane)
        return;
    QString nazwa = k_dane->getNazwa();
    int sila = k_dane->getSila();
    bool isLeg = k_dane->getLeg();
    Kategoria typKarty = k_dane->getKategoria();
    Efekt efektKarty = k_dane->getKeyword();
    //na razie to zostawiam, potem możemy zmienić na jakas grafikę
    QString borderStyle;
    if(isLeg==true) {
        borderStyle = "#91873a";
    }
    else {
        switch (efektKarty) {

        case Szpieg: {
            borderStyle = "#1e1e1e";
            break;
        }

        case Przyzwij: {
            borderStyle = "#2f3980";
            break;
        }

        case Linked: {
            borderStyle = "#79aba7";
            break;
        }

        case Reborn: {
            borderStyle = "#ff213b";
            break;
        }

        case Pogoda: {
            borderStyle = "#7ebdfc";
            break;
        }

        case Porzoga: {
            borderStyle = "#5eb04c";
            break;
        }

        case Horn: {
            borderStyle = "#a65a28";
            break;
        }

        case Boost: {
            borderStyle = "#8a555c";
            break;
        }

        case Morph: {
            borderStyle = "#661a5f";
            break;
        }

        case Grzyb: {
            borderStyle = "#095700";
            break;
        }

        case Kukla: {
            borderStyle = "#b8b693";
            break;
        }

        default: {
            borderStyle = "#787878";
            break;
        }

        }
    }

    QString style = QString(
                        "QPushButton {"
                        "  background-color: %1;"
                        "  color: white;"
                        "  border: 2px solid black;"
                        "  border-radius: 5px;"
                        "font: 10px;"
                        "}"
                        ":hover { border:#ffffff ; }"
                        "QPushButton:hover {"
                        "  border: 3px solid #f2eded;"
                        "}"
                        ).arg(borderStyle);

    this->setStyleSheet(style);

    QString name = "";
    QString sila_text = "";
    QString kategoria_text;
    for (int i = 0 ; i < k_dane->getNazwa().size() ; i++) {
        if (k_dane->getNazwa()[i].isSpace())        //nie wiem o co się śmieć pulta ale działa
            name = name + '\n';
        else
            name = name + k_dane->getNazwa()[i];
    }

    switch ( typKarty ) {
        case Melee: {
            kategoria_text = "Wręcz";
            break;
        }
        case Ranged: {
            kategoria_text = "Dystans";
            break;
        }
        case Siege: {
            kategoria_text = "Oblężenie";
            break;
        }
        default: {
            kategoria_text = "";
            break;
        }
    }

    if (k_dane->getKategoria() != Spell && k_dane->getKategoria() != Leader)
        sila_text = "Siła: " + QString::number( sila );

    this->setText( name + "\n\n" + kategoria_text + "\n" + sila_text);
}

int Card_Button::getIndeks(){
    return indeks;
}
