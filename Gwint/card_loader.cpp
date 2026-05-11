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
        Karta->nazwa = "error: File not found";
        return;
    }

    QTextStream in(&file);

    QString line;

    for (int i = 0; i <= id; i++)
    {
        if (in.atEnd()){
            Karta->nazwa = "error: end of file";
            return;
        }

        line = in.readLine();
    }

    file.close();

    QStringList dane = line.split(';'); //rozdziela tekst na listę używając znaku ; jako separator

    Karta->id = dane[0].toInt(nullptr, 10);
    //na wszelki wypadek odczytuję id z pliku żeby upewnić
    //się czy odpowiednia karta zosała odczytana

    Karta->nazwa = dane[1];



    //wiem że to wygląda tragicznie i jakby to zrobił jaskiniowiec
    //ale c++ nie akceptuje stringów do SWITCHa
    if (dane[2] == "NORTHERN")
        Karta->frakcja = Frakcja::Polnoc;
    else if (dane[2] == "SCOIA'TAEL")
        Karta->frakcja = Frakcja::Elfy;
    else if (dane[2] == "MONSTERS")
        Karta->frakcja = Frakcja::Potwory;
    else if (dane[2] == "NILFGAARD")
        Karta->frakcja = Frakcja::Niflgard;
    else if (dane[2] == "SKELLIGE")
        Karta->frakcja = Frakcja::Skelige;
    else
        Karta->frakcja = Frakcja::Neutral;

    if (dane[3] == "MELEE")
        Karta->kategoria = Kategoria::Melee;
    else if (dane[3] == "RANGED")
        Karta->kategoria = Kategoria::Ranged;
    else if (dane[3] == "SIEGE")
        Karta->kategoria = Kategoria::Siege;
    else if (dane[3] == "SPELL")
        Karta->kategoria = Kategoria::Spell;
    else if (dane[3] == "LEADER")
        Karta->kategoria = Kategoria::Leader;
    else if (dane[3] == "AGILE")
        Karta->kategoria = Kategoria::Agile;
    else {
        Karta->kategoria = Kategoria::Undefined;
        Karta->nazwa = "Error: typ karty niezdefiniowany";
        return;
        //jeśli odczytana karta nie ma typu to nie jest działająca karta
    }


    Karta->sila_bazowa = dane[4].toInt(nullptr, 10);
    Karta->sila = Karta->sila_bazowa;

    Karta->efekt = nullptr;  //to do zrobienia jak zostaną zaimplementowane keywordy
//    odczytana_karta.cele = dane[6];  //to tak samo
    Karta->max_w_talii = dane[7].toInt(nullptr, 10);
    if (dane[8] == '1') Karta->legendarna = true;

    Karta->flavor_text = dane[9];

    return;
}