#ifndef FOURACEGAME_H
#define FOURACEGAME_H
#include "table.h"
#include "card.h"
#include <QList>

class FourAceGame
{
public:
    FourAceGame();
    bool playRound();
private:
    QList<Card> m_deck;
    Table m_table;
    void resetDeck();
    void shuffle();
    void cleanUp();
};

#endif // FOURACEGAME_H
