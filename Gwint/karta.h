#ifndef KARTA_H
#define KARTA_H
#include <QString>
#include "keyword.h"
#include <vector>

enum Frakcja {
    Neutral, Elfy, Polnoc, Niflgard, Skelige, Potwory
};

enum Kategoria {
    Spell, Melee, Siege, Ranged, Agile, Leader, Undefined
};

class karta
{
public:
    karta();

//
//  dla uniknięcia pomyłek stuktury z klasą stuktura ma nazwę po angielsku
//
//  struktura card to odczytywana z pliku karta która będzie obsługiwana przez
//  wszystkie inne obiekty (odpowiednik bloczka FBD z poprzedniego projektu)
//
//  opis wszystkich pól:
//
//  id - jest to unikalny numer karty używany do szybkiego odczytywania karty
//  z pliku cards_list.txt gdzie są przechowywane wszystkie karty
//
//  nazwa - nazwa karty która się będzie wyświetlać dla użytkownika
//
//  frakcja - definiuje do której talii może należeć karta
//  Neutral może należeć do dowolnej
//
//  siła_bazowa - liczbowa siła karty odczytana z pliku
//
//  sila - sila karty po uwzglednieniu efektów innych kart na tą kartę
//
//  efekt - adres do obiektu dziedziczącego po klasie keyword
//  określa jaki efekt będzie miała karta
//
//  cele - wektor kart, i obszarów gry na które działa dany efekt
//
//  max_w_talii - określa ile maksymalnie można mieć kopii karty w talii w trakcie jej tworzenia
//
//  legenda - ogreśla czy karta jest kartą legendarną czy nie
//  czyli taką na którą nie działają efekty innych kart
//
//  flavor_text - dodatkowy teks na karcie który na nią nie wpływa
//  ale po prostu jest dla ozdoby
//
    struct Card{
        unsigned int id = 0;
        QString nazwa = "null";
        Frakcja frakcja = Frakcja::Neutral;
        Kategoria kategoria = Kategoria::Undefined;
        int sila_bazowa = 0;
        int sila = 0;
        keyword *efekt = nullptr;
        std::vector<int> cele;
        unsigned int max_w_talii = 0;
        bool legendarna = false;
        QString flavor_text = "";
    };

    //~karta();
};


//testuję czy dział

#endif // KARTA_H
