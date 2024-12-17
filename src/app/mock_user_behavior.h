#ifndef MOCKUSERBEHAVIOR_H
#define MOCKUSERBEHAVIOR_H

#include <QObject>
#include <QTimer>
#include <QMap>
#include <QRecursiveMutex>
#include <QMutexLocker>

#include "engine/matchmaking/matchmaking_engine.h"
#include "engine/pool/user_pool_manager.h"

class MockUserBehavior : public QObject
{
    Q_OBJECT

public:
    explicit MockUserBehavior(UserPoolManager* userPoolManager, MatchmakingEngine* matchmakingEngine, QObject* parent = nullptr);

private slots:
    void onUserStateChanged(const QString& username, UserState oldState, UserState newState);

private:
    void startMatchRequestTimer(const QString& username);
    void stopMatchRequestTimer(const QString& username);

    UserPoolManager* m_userPoolManager;
    MatchmakingEngine* m_matchmakingEngine;

    QMap<QString, QTimer*> m_userTimers;
    QRecursiveMutex m_mutex;
};

#endif // MOCKUSERBEHAVIOR_H
