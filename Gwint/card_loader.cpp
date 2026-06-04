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

    qDebug() << "Ładowanie karty";
    QString fileName = "cards_list.txt";
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Nie znaleziono pliku";
        return;
    }

    QTextStream in(&file);

    QString line;

    for (int i = 0; i <= id; i++)
    {
        if (in.atEnd()){
            qDebug() << "Koniec Pliku";
            return;
        }

        line = in.readLine();
    }

    file.close();

    QStringList dane = line.split(';'); //rozdziela tekst na listę używając znaku ; jako separator

    Karta->setID(dane[0].toInt(nullptr));
    Karta->setName(dane[1]);
    Karta->setFrakcja(dane[2]);
    Karta->setKategoria(dane[3]);
    Karta->setSilaBaz(dane[4].toInt(nullptr));
    Karta->updateSila(0,0,0);
    Karta->setKeyword(dane[5]);
    Karta->setCele(dane[6]);
    Karta->setMax(dane[7].toInt(nullptr));
    if (dane[8] == '1') Karta->setLeg(true);
    Karta->setFlavor(dane[9]);

    qDebug() << "Załadowano z pliku karte: " + dane[1];

    return;
}
