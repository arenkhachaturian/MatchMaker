#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewers/user_table/user_table_widget.h"
#include "viewers/dashboard/dashboard_widget.h"
#include "viewers/toolbar/app_toolbar.h"
#include "mainwindow.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::setupWindow(UserTableWidget *userTableWidget, DashboardWidget *dashboardWidget, AppToolbar *toolbar)
{
    m_userTableWidget = userTableWidget;
    m_dashboardWidget = dashboardWidget;
    m_toolbar = toolbar;

    addToolBar(Qt::TopToolBarArea, m_toolbar);

    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(m_dashboardWidget);
    splitter->addWidget(m_userTableWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 1);

    this->setCentralWidget(splitter);

    setupConnections();
}

void MainWindow::setupConnections()
{
    // TODO: make save dashboard private again
    connect(m_toolbar, &AppToolbar::saveDashboardRequested, this, [this]()
            { m_dashboardWidget->saveDashboardToFile(); });

    // TODO: add middleware here and make slots private again
    connect(m_toolbar, &AppToolbar::addUserRequested, [&]()
            { m_userTableWidget->onAddUser(); });

    connect(m_toolbar, &AppToolbar::removeUserRequested, [&]()
            { m_userTableWidget->onRemoveUser(); });

    connect(m_toolbar, &AppToolbar::toggleDashboardViewRequested, this, [this]()
            { m_dashboardWidget->setVisible(!m_dashboardWidget->isVisible()); });

    connect(m_toolbar, &AppToolbar::toggleUserListViewRequested, this, [this]()
            { m_userTableWidget->setVisible(!m_userTableWidget->isVisible()); });
}

MainWindow::~MainWindow()
{
    delete ui;
}
