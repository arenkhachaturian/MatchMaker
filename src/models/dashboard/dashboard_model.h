#ifndef DASHBOARD_MODEL_H
#define DASHBOARD_MODEL_H

#include "engine/game/game_registry.h"
#include "engine/user/user_registry.h"
#include <QAbstractItemModel>

class DashboardModel final : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit DashboardModel(GameRegistry* gameRegistry, UserRegistry* userRegistry, QObject* parent = nullptr);

    const Game& getGame(const QString& gameName) const;
    QStringList getAllGameNames() const;

    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void onGameRemoved(const QString& gameName);
    void onGameAdded(const QString& gameName);
    void onUserChanged(const QString& userName, int row, UserRegistry::ChangeType changeType);

private:
    GameRegistry* m_gameRegistry;
    UserRegistry* m_userRegistry;

    struct TreeNode {
        QString gameName;
        QString username;
        QString rating;
        QVector<TreeNode*> children;
    };

    QVector<TreeNode*> m_rootNodes; // game as root node

    void buildTree();
};

#endif // DASHBOARD_MODEL_H
