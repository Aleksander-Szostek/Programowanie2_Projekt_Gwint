#include "deck_loader.h"
#include <QFile>
#include <QTextStream>

deck_loader::deck_loader() {}

std::vector<karta*> deck_loader::load_deck(QString fileName){

    QFile file(fileName);

    std::vector<karta*> Zaladowane;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        karta* z_karta = new karta;
        z_karta->setName("Error: lack of deck file");
        Zaladowane.push_back(z_karta);
        return Zaladowane;
    }

    QTextStream in(&file);

    QString line;

    if (in.atEnd()){
        karta* z_karta = new karta;
        z_karta->setName("Error: empty deck file");
        Zaladowane.push_back(z_karta);
        return Zaladowane;
    }

    line = in.readLine();

    file.close();

    QStringList dane = line.split(';');

    card_loader wtasowyacz_kart;

    for (int i = 0; i < dane.size(); i++) {
        karta* z_karta = new karta;
        wtasowyacz_kart.zaladuj_karte(dane[i].toInt(nullptr, 10), z_karta);
        Zaladowane.push_back(z_karta);
    }


    return Zaladowane;
}
