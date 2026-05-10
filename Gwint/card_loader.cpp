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
karta::Card card_loader::zaladuj_karte(int id) {

    QString fileName = "cards_list.txt";
    QFile file(fileName);
    karta::Card odczytana_karta;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        odczytana_karta.nazwa = "error: File not found";
        return odczytana_karta;
    }

    QTextStream in(&file);

    QString line;

    for (int i = 0; i <= id; i++)
    {
        if (in.atEnd()){
            odczytana_karta.nazwa = "error: end of file";
            return odczytana_karta;
        }

        line = in.readLine();
    }

    file.close();

    QStringList dane = line.split(';'); //rozdziela tekst na listę używając znaku ; jako separator

    odczytana_karta.id = dane[0].toInt(nullptr, 10);
    //na wszelki wypadek odczytuję id z pliku żeby upewnić
    //się czy odpowiednia karta zosała odczytana

    odczytana_karta.nazwa = dane[1];



    //wiem że to wygląda tragicznie i jakby to zrobił jaskiniowiec
    //ale c++ nie akceptuje stringów do SWITCHa
    if (dane[2] == "NORTHERN")
        odczytana_karta.frakcja = Frakcja::Polnoc;
    else if (dane[2] == "SCOIA'TAEL")
        odczytana_karta.frakcja = Frakcja::Elfy;
    else if (dane[2] == "MONSTERS")
        odczytana_karta.frakcja = Frakcja::Potwory;
    else if (dane[2] == "NILFGAARD")
        odczytana_karta.frakcja = Frakcja::Niflgard;
    else if (dane[2] == "SKELLIGE")
        odczytana_karta.frakcja = Frakcja::Skelige;
    else
        odczytana_karta.frakcja = Frakcja::Neutral;

    if (dane[3] == "MELEE")
        odczytana_karta.kategoria = Kategoria::Melee;
    else if (dane[3] == "RANGED")
        odczytana_karta.kategoria = Kategoria::Ranged;
    else if (dane[3] == "SIEGE")
        odczytana_karta.kategoria = Kategoria::Siege;
    else if (dane[3] == "SPELL")
        odczytana_karta.kategoria = Kategoria::Spell;
    else if (dane[3] == "LEADER")
        odczytana_karta.kategoria = Kategoria::Leader;
    else if (dane[3] == "AGILE")
        odczytana_karta.kategoria = Kategoria::Agile;
    else {
        odczytana_karta.kategoria = Kategoria::Undefined;
        return odczytana_karta;
        //jeśli odczytana karta nie ma typu to nie jest działająca karta
    }


    odczytana_karta.sila_bazowa = dane[4].toInt(nullptr, 10);
    odczytana_karta.sila = odczytana_karta.sila_bazowa;
    odczytana_karta.efekt = nullptr;  //to do zrobienia jak zostaną zaimplementowane keywordy
//    odczytana_karta.cele = dane[6];  //to tak samo
    odczytana_karta.max_w_talii = dane[7].toInt(nullptr, 10);
    if (dane[8] == '1') odczytana_karta.legendarna = true;

    odczytana_karta.flavor_text = dane[9];

    return odczytana_karta;

}