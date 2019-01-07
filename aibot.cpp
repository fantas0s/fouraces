#include "aibot.h"

void AIBot::play(quint32 times)
{
    m_successes = 0;
    while (times) {
        if (m_game.playRound())
            m_successes++;
        times--;
    }
}

quint32 AIBot::getNumOfPassedGames() const
{
    return m_successes;
}
