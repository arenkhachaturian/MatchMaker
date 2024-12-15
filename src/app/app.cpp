#include "app.h"
#include "config.h"
#include "engine/io/json_io_handler.h"
#include "engine/game/game.h"
#include "engine/game/game_registry.h"
#include "engine/game/game_executor.h"
#include "engine/pool/user_pool_manager.h"
#include "engine/user/user_registry.h"
#include "engine/matchmaking/matchmaking_engine.h"
#include "models/dashboard/dashboard_model.h"
#include "models/dashboard/dashboard_serializer.h"
#include "models/user_table/user_table_model.h"
#include "viewers/dashboard/dashboard_widget.h"
#include "viewers/user_table/user_table_widget.h"
#include "viewers/mainwindow/mainwindow.h"
#include "viewers/toolbar/app_toolbar.h"

#include <QRandomGenerator>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QDir>

App::App(QObject *parent)
    : w{}, QObject{parent}
{
    QString user_data_path = QDir::toNativeSeparators(USER_DATA_FILE);
    QString game_data_path = QDir::toNativeSeparators(GAME_DATA_FILE);

    m_userIoHandler = new JsonIOHandler(user_data_path);
    m_gameIoHandler = new JsonIOHandler(game_data_path);

    m_userRegistry = new UserRegistry(this);
    m_gameRegistry = new GameRegistry(this);
    m_userPoolManager = new UserPoolManager(this);
    m_gameExecutor = new GameExecutor(this);

    auto users = m_userIoHandler->readUsers();
    auto games = m_gameIoHandler->readGames();

    for (const auto &user : users)
    {
        m_userRegistry->addUser(user);
    }
    for (const auto &game : games)
    {
        m_gameRegistry->addGame(game);
    }
    for (const auto &user : users)
    {
        m_userPoolManager->addUser(user.getUsername());
    }

    m_matchmakingEngine = new MatchmakingEngine(m_userPoolManager, m_userRegistry, m_gameRegistry,
                                                    m_gameExecutor, this);

    m_dashboardModel = new DashboardModel(m_gameRegistry, m_userRegistry, this);
    m_userTableModel = new UserTableModel(m_userRegistry, this);

    m_dashboardWidget = new DashboardWidget(m_dashboardModel, &w);
    m_userTableWidget = new UserTableWidget(m_userTableModel, m_dashboardModel, &w);
    m_appToolbar = new AppToolbar(&w);

    w.setupWindow(m_userTableWidget, m_dashboardWidget, m_appToolbar);
    w.resize(1200, 600);
    w.show();

    // Mocking user behaviour
    m_timer = new QTimer(this);
    QObject::connect(m_timer, &QTimer::timeout, [this]()
        {
            auto users = m_userRegistry->getAllUsers();

            if (!users.isEmpty()) {
                int randomIndex = QRandomGenerator::global()->bounded(users.size());
                const QString& username = users[randomIndex].getUsername();
                qDebug() << "Requesting match for user:" << username;
                m_matchmakingEngine->requestMatch(username);
            } else {
                qDebug() << "No users available in the registry.";
            }
        }
    );

    m_timer->start(2000);
    m_matchmakingEngine->start(2000);
}

App::~App()
{
    m_userIoHandler->writeUsers(m_userRegistry->getAllUsers());
    m_gameIoHandler->writeGames(m_gameRegistry->getAllGames());
    delete m_userIoHandler;
    delete m_gameIoHandler;
}
