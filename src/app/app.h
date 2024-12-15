#ifndef APP_H
#define APP_H

#include "viewers/mainwindow/mainwindow.h"
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

#include <QObject>
#include <QTimer>

class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = nullptr);
    virtual ~App();

    MainWindow w;
    IOHandler* m_userIoHandler;
    IOHandler* m_gameIoHandler; 
    MatchmakingEngine* m_matchmakingEngine;
    GameRegistry* m_gameRegistry;
    UserRegistry* m_userRegistry;
    GameExecutor* m_gameExecutor;
    UserPoolManager* m_userPoolManager;
    DashboardModel* m_dashboardModel;
    UserTableModel* m_userTableModel;
    DashboardWidget* m_dashboardWidget;
    UserTableWidget* m_userTableWidget;
    AppToolbar* m_appToolbar;
    QTimer* m_timer;
};

#endif // APP_H
