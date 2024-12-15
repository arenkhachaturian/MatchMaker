#include "engine/game/game_registry.h"
#include <stdexcept>
#include <string>

GameRegistry::GameRegistry(QObject *parent)
    : QObject(parent) {}

bool GameRegistry::addGame(const Game &newGame)
{
    QMutexLocker locker(&mutex);
    if (m_games.indexOf(newGame) > 0)
    {
        return false;
    }
    m_games.append(newGame);
    emit gameAdded(newGame.getName());
    return true;
}

bool GameRegistry::removeGame(const QString &gameName)
{
    QMutexLocker locker(&mutex);
    std::size_t origSize = m_games.size();
    std::remove_if(m_games.begin(),
                    m_games.end(),
                    [&](const Game &game)
                    {
                        return game.getName() == gameName;
                    });

    if (origSize == m_games.size() - 1) {
        emit gameRemoved(gameName);
        return true;
    }
    return false;
}

const Game& GameRegistry::getGame(const QString &gameName) const
{
    QMutexLocker locker(&mutex);
    auto it = std::find_if(m_games.begin(),
                        m_games.end(),
                        [&](const Game &game)
                        {
                            return game.getName() == gameName;
                        });
    if (it == m_games.end()) {
        throw std::runtime_error(std::string("Game ") + gameName.toStdString() + " not found");
    }
    return *it;
}

const QList<Game>& GameRegistry::getAllGames() const
{
    QMutexLocker locker(&mutex);
    return m_games;
}
