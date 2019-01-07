#include "fouracegame.h"
#include <QDateTime>

/* 0.0005% passrate if no moving is done and pass criteria is having only aces on table. */
/* 0.485% passrate if no moving is done and pass criteria is having top cards as aces. */
/* 2.5% (1 to 40) passrate if moving is done based on getting minimum amount of cards left on table and pass criteria is having only aces on table. */
/* 5.75% (1 to 18) passrate if moving is done based on getting minimum amount of cards left on table and pass criteria is having top cards as aces. */

FourAceGame::FourAceGame()
{
    qsrand(QDateTime::currentDateTime().toSecsSinceEpoch());
    resetDeck();
    m_table.reset();
}

void FourAceGame::resetDeck()
{
    m_deck.clear();
    for (int suite = 0 ; suite < 4 ; ++suite) {
        for (int number = 2 ; number < 15 ; ++number) {
            Card card((Card::Suite)suite, number);
            m_deck.append(card);
        }
    }
}

void FourAceGame::shuffle()
{
    for (int index = 0 ; index < 52 ; ++index) {
        Card storedCard = m_deck.at(index);
        int copyIdx = qrand() % 52;
        m_deck[index] = m_deck.at(copyIdx);
        m_deck[copyIdx] = storedCard;
    }
}

void FourAceGame::cleanUp()
{
    bool cardRemoved;
    bool cardMoved;
    do {
        cardRemoved = m_table.removeCardsOfSameSuite();
        cardMoved = m_table.moveCardToEmptySlot();
    } while (cardRemoved || cardMoved);
}

bool FourAceGame::playRound()
{
    m_table.reset();
    resetDeck();
    shuffle();
    while (m_deck.length()) {
        m_table.deal(m_deck);
        cleanUp();
    }
    return m_table.onlyAcesOnTable();
}
