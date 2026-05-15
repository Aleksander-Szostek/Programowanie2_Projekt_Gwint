#ifndef DECK_H
#define DECK_H
#include "kontener_kart.h"

class deck : public kontener_kart {

public:
    deck();

    void makeDeck(QString deckFile);

    void validifyDeck();

private:

    kontener_kart Leader;           //pomimo że to pole nie powinno zawierać więcej niż 1 karta
                                    //to jest kontenerem żeby kożystało z tych samych funkcji co taliia

    const bool isDeck() override;

    Frakcja FrakcjaTalii = Frakcja::Neutral;

    bool DeckValid = false;
};

#endif // DECK_H
