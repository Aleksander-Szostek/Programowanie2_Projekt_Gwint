#ifndef DECK_H
#define DECK_H
#include "kontener_kart.h"
#include "deck_loader.h"

class deck : public kontener_kart {

public:
    deck();

    void makeDeck(QString deckFile);

    void makeDeckZUI(const std::vector<karta*>& wybraneKarty);

    void validifyDeck();

    kontener_kart* getLeader();      //pomimo że to pole nie powinno zawierać więcej niż 1 karta
                                //to jest kontenerem żeby kożystało z tych samych funkcji co każdy inny kontener kart
    bool DeckValid = true; //false;



private:

    kontener_kart *Leader;

    bool isDeck = true;

    Frakcja FrakcjaTalii = Frakcja::Neutral;
};

#endif // DECK_H
