#include "efekty_pogodowe.h"

efekty_pogodowe::efekty_pogodowe() {}

bool efekty_pogodowe::isMeleePogoda(){
    return scanLine(-1);
}
bool efekty_pogodowe::isRangePogoda(){
    return scanLine(-2);
}
bool efekty_pogodowe::isSiegePogoda(){
    return scanLine(-3);
}

bool efekty_pogodowe::scanLine(int nr_linii){
    for (int i = 0 ; i < getDeckSize() ; i++) {
        for (int j = 0 ; j < getKartaFromList(i)->getCele().size() ; j++) {
            if (getKartaFromList(i)->getCele().at(j) == nr_linii)
                return true;
        }
    }

    return false;
}

void efekty_pogodowe::wyczysc() {
    while (getDeckSize() > 0) {
        this->delete_card(0);
    }
}