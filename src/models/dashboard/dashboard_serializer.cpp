#include "dashboard_serializer.h"
#include "models/dashboard/dashboard_model.h"
#include <QModelIndex>
#include <QJsonArray>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <cstddef>

QJsonDocument DashboardSerializer::serializeToJson(const DashboardModel *model, const QString &gameName)
{
    QJsonObject rootObject;

    for (std::size_t i = 0; i < model->rowCount(); ++i)
    {
        QModelIndex gameIndex = model->index(i, 0);
        if (model->data(gameIndex, Qt::DisplayRole).toString() == gameName)
        {
            QJsonArray usersArray;
            for (std::size_t j = 0; j < model->rowCount(gameIndex); ++j)
            {
                QModelIndex userIndex = model->index(j, 0, gameIndex);
                QString username = model->data(userIndex.siblingAtColumn(1), Qt::DisplayRole).toString();
                QString rating = model->data(userIndex.siblingAtColumn(2), Qt::DisplayRole).toString();

                QJsonObject userObject;
                userObject["username"] = username;
                userObject["rating"] = rating;
                usersArray.append(userObject);
            }

            rootObject["game"] = gameName;
            rootObject["users"] = usersArray;
            break;
        }
    }

    return QJsonDocument(rootObject);
}

QJsonDocument DashboardSerializer::serializeToJson(const DashboardModel *model)
{
    QJsonArray gamesArray;

    for (std::size_t i = 0; i < model->rowCount(); ++i)
    {
        QModelIndex gameIndex = model->index(i, 0);
        QString gameName = model->data(gameIndex, Qt::DisplayRole).toString();

        QJsonDocument gameDocument = serializeToJson(model, gameName);
        gamesArray.append(gameDocument.object());
    }

    QJsonObject rootObject;
    rootObject["dashboard"] = gamesArray;

    return QJsonDocument(rootObject);
}
