#include "deck_saver.h"
#include <fstream>
#include "kontener_kart.h"
#include <string>

deck_saver::deck_saver() {}

void deck_saver::save_deck(kontener_kart &talia_do_zapisania, QString fileName){

    //pracuje na stringach bo są znacznie lepiej udokumentowane niż QStringi i łatwiej się robi
    std::string file_string = "";

    //file_string += std::to_string(talia_do_zapisania.Ciag_kart[0]->getID());
    //for (int i = 1; i < talia_do_zapisania.Ciag_kart.size(); i++) {
    //    file_string += ";";
    //    file_string += std::to_string(talia_do_zapisania.Ciag_kart[i]->getID());
    //}

    std::ofstream file(fileName.toStdString());

    if (!file.good())
    {
        return;
    }

    file << file_string;
    file.close();

    return;
}