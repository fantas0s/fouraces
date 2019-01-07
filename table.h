#ifndef TABLE_H
#define TABLE_H
#include <QList>
#include "card.h"

class Table;

class Table
{
public:
    Table();
    Table(const Table &source);
    void deal(QList<Card> &listRef);
    bool onlyAcesOnTable();
    bool topCardsAreAllAces();
    bool largerFromSameSuiteExists(Card comparison);
    void reset();
    bool removeCardsOfSameSuite();
    bool moveCardToEmptySlot();
private:
    quint32 cardsOnTable();
    quint32 getLeastCardsIfMoveToEmpty(int fromIndex, int emptyIndex);
    QList<Card> m_table[4];
    void moveCard(int from, int to);
    int getEmptySlotIndex();
    int getIndexOfBestCardToMove();
};

#endif // TABLE_H
