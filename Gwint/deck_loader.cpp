#include "deck_loader.h"
#include <QFile>
#include <QTextStream>
#include "card_loader.h"
#include "kontener_kart.h"

deck_loader::deck_loader() {}

void deck_loader::load_deck(kontener_kart &talia_do_wczytania, QString fileName){

    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        talia_do_wczytania.Ciag_kart[0]->nazwa = "Error: lack od deck file";
        return;
    }

    QTextStream in(&file);

    QString line;

    if (in.atEnd()){
        talia_do_wczytania.Ciag_kart[0]->nazwa = "Error: empty deck file";
        return;
    }

    line = in.readLine();

    file.close();

    QStringList dane = line.split(';');

    card_loader wtasowyacz_kart;

    for (int i = 0; i < dane.size(); i++) {
        karta* zaladowana_karta = new karta;
        wtasowyacz_kart.zaladuj_karte(dane[i].toInt(nullptr, 10), zaladowana_karta);
        talia_do_wczytania.Ciag_kart.push_back(zaladowana_karta);
    }


    return;
}
