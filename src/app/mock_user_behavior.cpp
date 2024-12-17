#include "mock_user_behavior.h"

MockUserBehavior::MockUserBehavior(UserPoolManager* userPoolManager, MatchmakingEngine* matchmakingEngine, QObject* parent)
    : QObject(parent), m_userPoolManager(userPoolManager), m_matchmakingEngine(matchmakingEngine)
{
    connect(m_userPoolManager, &UserPoolManager::userStateChanged, this, &MockUserBehavior::onUserStateChanged);
}

void MockUserBehavior::onUserStateChanged(const QString& username, UserState oldState, UserState newState)
{
    QMutexLocker locker(&m_mutex);

    if (newState == UserState::Free) {
        startMatchRequestTimer(username);
    } else {
        stopMatchRequestTimer(username);
    }
}

void MockUserBehavior::startMatchRequestTimer(const QString& username)
{
    if (!m_userTimers.contains(username)) {
        QTimer* timer = new QTimer(this);
        timer->setSingleShot(true);

        connect(timer, &QTimer::timeout, this, [this, username]() {
            QMutexLocker locker(&m_mutex);
            m_matchmakingEngine->requestMatch(username);
            m_userTimers.remove(username);
        });

        m_userTimers.insert(username, timer);
        timer->start(2000);
    }
}

void MockUserBehavior::stopMatchRequestTimer(const QString& username)
{
    if (m_userTimers.contains(username)) {
        QTimer* timer = m_userTimers.take(username);
        timer->stop();
        timer->deleteLater();
    }
}
