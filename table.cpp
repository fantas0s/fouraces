#include "table.h"

Table::Table()
{
    reset();
}

Table::Table(const Table &source)
{
    reset();
    for (int index = 0 ; index < 4 ; ++index) {
        foreach (const Card card, source.m_table[index]) {
            m_table[index].append(card);
        }
    }
}

void Table::reset()
{
    for (int index = 0 ; index < 4 ; ++index) {
        m_table[index].clear();
    }
}

void Table::deal(QList<Card> &listRef)
{
    for (int index = 0 ; index < 4 ; ++index) {
        if (!listRef.isEmpty()) {
            Card fromTop = listRef.last();
            listRef.removeLast();
            m_table[index].append(fromTop);
        }
    }
}

bool Table::removeCardsOfSameSuite()
{
    bool gameChanged = false;
    bool cardRemoved;
    do {
        cardRemoved = false;
        for (int index = 0 ; index < 4 ; ++index) {
            if (!m_table[index].isEmpty()) {
                Card fromTop = m_table[index].last();
                if (largerFromSameSuiteExists(fromTop)) {
                    m_table[index].removeLast();
                    gameChanged = true;
                    cardRemoved = true;
                }
            }
        }
    } while(cardRemoved);
    return gameChanged;
}

quint32 Table::cardsOnTable()
{
    quint32 retval = 0;
    for (int index = 0 ; index < 4 ; ++index) {
        retval += m_table[index].length();
    }
    return retval;
}

void Table::moveCard(int from, int to)
{
    Card takenCard = m_table[from].last();
    m_table[from].removeLast();
    m_table[to].append(takenCard);
}

int Table::getEmptySlotIndex()
{
    for (int index = 0 ; index < 4 ; ++index) {
        if (m_table[index].isEmpty()){
            return index;
        }
    }
    return -1;
}

int Table::getIndexOfBestCardToMove()
{
    quint32 remainingCards[4] = {52,52,52,52};
    for (int index = 0 ; index < 4 ; ++index) {
        if (m_table[index].length() > 1) {
            Table copyTable(*this);
            remainingCards[index] = copyTable.getLeastCardsIfMoveToEmpty(index, getEmptySlotIndex());
        }
    }
    int bestIndex = -1;
    quint32 leastCards = 52;
    for (int index = 0 ; index < 4 ; ++index) {
        if (remainingCards[index] < leastCards) {
            leastCards = remainingCards[index];
            bestIndex = index;
        }
    }
    return bestIndex;
}

bool Table::moveCardToEmptySlot()
{
    int emptySlotIndex = getEmptySlotIndex();
    if ((emptySlotIndex >= 0) &&
        (cardsOnTable() >= 4)) {
        int bestIndex = getIndexOfBestCardToMove();
        if (bestIndex >= 0) {
            moveCard(bestIndex, emptySlotIndex);
            return true;
        }
    }
    return false;
}

quint32 Table::getLeastCardsIfMoveToEmpty(int fromIndex, int emptyIndex)
{
    moveCard(fromIndex, emptyIndex);
    removeCardsOfSameSuite();
    if ((getEmptySlotIndex() >= 0) && /* we have empty slot AND */
        (cardsOnTable() >= 4)) { /* we won't just move same card back and forth */
        int nextMove = getIndexOfBestCardToMove();
        if (nextMove >= 0) {
            return getLeastCardsIfMoveToEmpty(nextMove, getEmptySlotIndex());
        }
    }
    return cardsOnTable();
}

bool Table::onlyAcesOnTable()
{
    if ((1 == m_table[0].length()) &&
        (1 == m_table[1].length()) &&
        (1 == m_table[2].length()) &&
        (1 == m_table[3].length()) &&
        (14 == m_table[0].at(0).number()) &&
        (14 == m_table[1].at(0).number()) &&
        (14 == m_table[2].at(0).number()) &&
        (14 == m_table[3].at(0).number()))
        return true;
    return false;
}

bool Table::topCardsAreAllAces()
{
    if (!m_table[0].isEmpty() &&
        !m_table[1].isEmpty() &&
        !m_table[2].isEmpty() &&
        !m_table[3].isEmpty() &&
        (14 == m_table[0].last().number()) &&
        (14 == m_table[1].last().number()) &&
        (14 == m_table[2].last().number()) &&
        (14 == m_table[3].last().number()))
        return true;
    return false;
}

bool Table::largerFromSameSuiteExists(Card comparison)
{
    for (int index = 0 ; index < 4 ; ++index) {
        if (!m_table[index].isEmpty() &&
            (comparison.suite() == m_table[index].last().suite()) &&
            (comparison.number() < m_table[index].last().number())){
            return true;
        }
    }
    return false;
}
