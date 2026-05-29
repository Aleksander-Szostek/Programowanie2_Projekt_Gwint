#ifndef KARTA_H
#define KARTA_H
#include <QString>
#include <vector>
#include <QDebug>

enum Frakcja {
    Neutral,
    Elfy,
    Polnoc,
    Niflgard,
    Skelige,
    Potwory
};

enum Kategoria {
    Spell,
    Melee,
    Siege,
    Ranged,
    Agile,
    Leader,
    Undefined
};

enum Efekt {
    Brak,
    Szpieg,
    Przyzwij,
    Linked,
    Medyk,
    Reborn,
    Pogoda,
    Porzoga,
    Horn,
    Boost,
    Morph,
    Grzyb
};

class karta
{
public:
    karta();

    void setID(unsigned int id_s);
    void setName(QString nazwa_s);
    void setFrakcja(QString Nazwa_frakcji);
    void setKategoria(QString Nazwa_kategorii);
    void setSilaBaz(unsigned int sila_bazowa_s);
    void setKeyword(QString efekt_s);
    void setCele(QString cele_s);
    void setMax(unsigned int max_w_talii_s);
    void setLeg(bool leg_s);
    void setFlavor(QString flavor_s);

    void updateSila(bool pogoda, bool horn, int boost);

    unsigned int getID();
    QString getNazwa();
    Frakcja getFrakcja();
    Kategoria getKategoria();
    unsigned int getSila();
    std::vector<int> getCele();

    Efekt getKeyword();

    unsigned int getMax();
    bool getLeg();
    QString getFlavor();

private:
    unsigned int id;
    QString nazwa = "null";
    Frakcja frakcja = Frakcja::Neutral;
    Kategoria kategoria = Kategoria::Undefined;
    int sila_bazowa = 0;
    int sila = 0;
    Efekt keyword = Brak;
    std::vector<int> cele;
    unsigned int max_w_talii = 0;
    bool legendarna = false;
    QString flavor_text = "";

    //~karta();
};

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

#endif // KARTA_H
