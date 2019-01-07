#include "card.h"

Card::Card(Suite newSuite, quint8 newNumber) :
    m_suite(newSuite),
    m_number(newNumber)
{
}
Card::Suite Card::suite() const
{
    return m_suite;
}

quint8 Card::number() const
{
    return m_number;
}
