#include "card_loader.h"
#include <QFile>
#include <QTextStream> //biblioteki umożliwiająca
//sczytywanie pliku bezpośrednio do QString (który ma polskie znaki)
#include <QDebug>



card_loader::card_loader() {}

//  funkcja która umożliwia w dowolnym monencie umieszczenie dowolne karty w dowolnym obiekcie przechowującym karty
//void wsadz_karte(kontener_kart *directory, int id, int pozycja) {
//    return;
//}


//  funkcja odczytuje kartę z pliku i zwraca do funkcji która wywołała
karta::Card card_loader::zaladuj_karte(int id) {
    karta::Card karta_odczytywana;

    QFile file("cards_list.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return karta_odczytywana;


    QStringList line;
    QTextStream in(&file);


    for(int i = 0; id >= i; i++)
    {
        line = in.readLine().split("\n");
    }

    karta_odczytywana.nazwa = line[0];


    return karta_odczytywana;
}