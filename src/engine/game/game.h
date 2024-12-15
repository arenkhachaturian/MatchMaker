#ifndef GAME_H
#define GAME_H

#include <QString>
#include <QHash>

class Game final
{
public:
    explicit Game(const QString &name, const QString &execPath = QString{});

    void setExecutablePath(const QString &executablePath);

    const QString &getName() const;
    const QString &getExecutablePath() const;

    bool operator==(const Game &other) const;

    friend uint qHash(const Game &game, uint seed);

private:
    QString m_name;
    QString m_executablePath;
};

inline uint qHash(const Game &game, uint seed = 0)
{
    return qHash(game.getName(), seed);
}

#endif // GAME_H
