#include "card_loader.h"
#include <QFile>
#include <QTextStream> //biblioteki umożliwiająca
//sczytywanie pliku bezpośrednio do QString (który ma polskie znaki)
//#include <QDebug>



card_loader::card_loader() {}

//  funkcja która umożliwia w dowolnym monencie umieszczenie dowolne karty w dowolnym obiekcie przechowującym karty
//void wsadz_karte(kontener_kart *directory, int id, int pozycja) {
//    return;
//}


//  funkcja odczytuje kartę z pliku i zwraca do funkcji która wywołała
void card_loader::zaladuj_karte(int id, karta* Karta) {

    QString fileName = "cards_list.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Karta->setName("error: file not found");
        return;
    }

    QTextStream in(&file);

    QString line;

    for (int i = 0; i <= id; i++)
    {
        if (in.atEnd()){
            Karta->setName("error: end of file");
            return;
        }

        line = in.readLine();
    }

    file.close();

    QStringList dane = line.split(';'); //rozdziela tekst na listę używając znaku ; jako separator

    Karta->setID(dane[0].toInt(nullptr, 10));
    Karta->setName(dane[1]);
    Karta->setFrakcja(dane[2]);
    Karta->setFrakcja(dane[3]);
    Karta->setSilaBaz(dane[4].toInt(nullptr, 10));
    Karta->updateSila(0,0,0);
//    Karta->efekt = nullptr;  //to do zrobienia jak zostaną zaimplementowane keywordy
//    odczytana_karta.cele = dane[6];
    Karta->setMax(dane[7].toInt(nullptr, 10));
    if (dane[8] == '1') Karta->setLeg(true);
    Karta->setFlavor(dane[9]);

    return;
}