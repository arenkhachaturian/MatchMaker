#include "viewers/mainwindow/mainwindow.h"
#include "viewers/user_table/user_table_widget.h"
#include "viewers/toolbar/app_toolbar.h"
#include "models/user_table/user_table_model.h"
#include "engine/user/user_registry.h"
#include "engine/game/game_registry.h"
#include "models/dashboard/dashboard_model.h"
#include "viewers/dashboard/dashboard_widget.h"
#include "engine/pool/user_pool_manager.h"
#include "engine/matchmaking/matchmaking_engine.h"
#include "engine/io/json_io_handler.h"
#include "app/app.h"
#include <QApplication>
#include <QSplitter>
#include <QDir>
#include <QRandomGenerator>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    App app;
    return a.exec();
}
