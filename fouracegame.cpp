#include "fouracegame.h"
#include <QDateTime>

FourAceGame::FourAceGame()
{
    qsrand(QDateTime::currentDateTime().toSecsSinceEpoch());
    resetDeck();
}

void FourAceGame::resetDeck()
{
    m_deck.clear();
    for (int suite = 0 ; suite < 4 ; ++suite) {
        for (int number = 2 ; number < 15 ; ++number) {
            Card card((Suite)suite, number);
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

void FourAceGame::dealFour()
{
    for (int index = 0 ; index < 4 ; ++index) {
        if (!m_deck.isEmpty()) {
            Card fromTop = m_deck.last();
            m_deck.removeLast();
            m_table[index].append(fromTop);
        }
    }
}

void FourAceGame::cleanUp()
{
    bool cardRemoved;
    do {
        cardRemoved = false;
        for (int index = 0 ; index < 4 ; ++index) {
            if (!m_table[index].isEmpty()) {
                Card fromTop = m_table[index].last();
                if (largerFromSameSuiteExists(fromTop)) {
                    m_table[index].removeLast();
                    cardRemoved = true;
                }
            }
        }
    } while(cardRemoved);
}

bool FourAceGame::onlyAcesOnTable()
{
    if ((1 == m_table[0].length()) &&
        (1 == m_table[1].length()) &&
        (1 == m_table[2].length()) &&
        (1 == m_table[3].length()) &&
        (14 == m_table[0].at(0).second) &&
        (14 == m_table[1].at(0).second) &&
        (14 == m_table[2].at(0).second) &&
        (14 == m_table[3].at(0).second))
        return true;
    return false;
}

bool FourAceGame::largerFromSameSuiteExists(Card comparison)
{
    for (int index = 0 ; index < 4 ; ++index) {
        if (!m_table[index].isEmpty() &&
            (comparison.first == m_table[index].last().first) &&
            (comparison.second < m_table[index].last().second)){
            return true;
        }
    }
    return false;
}

bool FourAceGame::playRound()
{
    resetDeck();
    shuffle();
    while (m_deck.length()) {
        dealFour();
        cleanUp();
    }
    return onlyAcesOnTable();
}
