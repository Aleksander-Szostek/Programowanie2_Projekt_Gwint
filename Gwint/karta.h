#ifndef KARTA_H
#define KARTA_H
#include <QString>
#include "keyword.h"
#include <vector>

enum Frakcja {
    Neutral, Elfy, Polnoc, Niflgard, Skelige, Potwory
};

enum Kategoria {
    Spell, Melee, Siege, Ranged, Agile, Leader
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
    struct Card{
        unsigned int id;
        QString nazwa;
        Frakcja frakcja;
        Kategoria kategoria;
        int sila_bazowa;
        int sila;
        keyword *efekt;
        std::vector<int> cele;
        unsigned int max_w_talii;
        bool legendarna;
    };

    ~karta();
};


//testuję czy dział

#endif // KARTA_H
