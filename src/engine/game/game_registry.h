#ifndef GAME_REGISTRY_H
#define GAME_REGISTRY_H

#include <memory>
#include "engine/game/game.h"
#include <QObject>
#include <QString>
#include <QSet>
#include <QRecursiveMutex>

class GameRegistry final : public QObject
{
    Q_OBJECT

public:
    explicit GameRegistry(QObject *parent = nullptr);

    bool addGame(const Game &newGame);
    bool removeGame(const QString &gameName);

    const Game& getGame(const QString &name) const;

    const QList<Game>& getAllGames() const;

signals:
    void gameAdded(const QString &name);
    void gameRemoved(const QString &name);

private:
    QList<Game> m_games;
    mutable QRecursiveMutex mutex;
};

#endif // GAME_REGISTRY_H
