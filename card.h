#ifndef CARD_H
#define CARD_H
#include <QtGlobal>
class Card
{
public:
    typedef enum {
        Heart = 0,
        Spade,
        Diamond,
        Club
    } Suite;
    Card(Suite newSuite, quint8 newNumber);
    Suite suite() const;
    quint8 number() const;
private:
    Card(){m_suite = Card::Heart; m_number=14;}
    Suite m_suite;
    quint8 m_number;
};

#endif // CARD_H
