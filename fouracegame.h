#ifndef FOURACEGAME_H
#define FOURACEGAME_H
#include <QPair>
#include <QVector>

class FourAceGame
{
public:
    FourAceGame();
    bool playRound();
private:
    typedef enum {
        Heart = 0,
        Spade,
        Diamond,
        Club
    } Suite;
    typedef QPair<Suite, int> Card;
    QVector<Card> m_deck;
    QVector<Card> m_table[4];
    void resetDeck();
    void shuffle();
    void dealFour();
    void cleanUp();
    bool onlyAcesOnTable();
    bool largerFromSameSuiteExists(Card comparison);
};

#endif // FOURACEGAME_H
