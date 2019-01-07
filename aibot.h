#ifndef AIBOT_H
#define AIBOT_H
#include <QObject>
#include "fouracegame.h"

class AIBot : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE void play(quint32 times);
    Q_INVOKABLE quint32 getNumOfPassedGames() const;
private:
    FourAceGame m_game;
    quint32 m_successes;
};

#endif // AIBOT_H
