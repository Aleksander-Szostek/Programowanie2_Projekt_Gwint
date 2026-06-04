#include "deck_saver.h"
#include <fstream>
#include <string>

deck_saver::deck_saver() {}

void deck_saver::save_deck(deck talia_do_zapisania, QString fileName){

    //pracuje na stringach bo są znacznie lepiej udokumentowane niż QStringi i łatwiej się robi
    talia_do_zapisania.validifyDeck();

    if (talia_do_zapisania.getDeckSize() == 0 || talia_do_zapisania.DeckValid != true || talia_do_zapisania.getLeader()->getKartaFromList(0)->getNazwa() == "")
        return;

    std::string file_string = "";

    file_string += std::to_string(talia_do_zapisania.getKartaFromList(0)->getID());
    for (int i = 1; i < talia_do_zapisania.getDeckSize(); i++) {
        file_string += ";";
        file_string += std::to_string(talia_do_zapisania.getKartaFromList(i)->getID());
    }



    std::ofstream file(fileName.toStdString());

    if (!file.good())
    {
        return;
    }

    file << file_string;
    file.close();

    return;
}