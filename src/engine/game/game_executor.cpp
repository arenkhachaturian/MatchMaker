#include "game_executor.h"
#include <QDebug>
#include <QThread>
#include <QRegularExpression>
#include <QFileInfo>


GameExecutor::GameExecutor(QObject *parent)
    : QObject(parent) {}


void GameExecutor::runGame(const Game &game, const QMap<QString, QString> &namedArgs)
{
    emit gameStarted(game.getName());
    if (!game.getExecutablePath().isEmpty())
    {
        runExecutableGame(game, namedArgs);
    }
    else
    {
        // TODO refactor
        emit gameFinished(game.getName(), GameResult{QStringList{}, QString{}, false});
    }
}

QStringList GameExecutor::convertNamedArgsToCommandLine(const QMap<QString, QString> &namedArgs) const
{
    QStringList args;
    for (auto it = namedArgs.begin(); it != namedArgs.end(); ++it)
    {
        args << "--" + it.key() << it.value();
    }
    return args;
}

void GameExecutor::runExecutableGame(const Game &game, const QMap<QString, QString> &namedArgs)
{
    if (game.getExecutablePath().isEmpty() || !QFileInfo::exists(game.getExecutablePath()))
    {
        emit gameFinished(game.getName(), GameResult{{}, "", false});
        qWarning() << "Game executable path is empty or does not exist for game:" << game.getName();
        return;
    }

    QString gameName = game.getName();
    QString execPath = game.getExecutablePath();
    QThread *thread = QThread::create([this, gameName, execPath, namedArgs]()
    {
        GameResult gameResult;
        gameResult.success = false;

        for (auto it = namedArgs.constBegin(); it != namedArgs.constEnd(); ++it) {
            if (it.key().contains("player")) {
                gameResult.players << it.value();
            }
        }
        QStringList args = convertNamedArgsToCommandLine(namedArgs);
        QProcess process;
        process.start(execPath, args);

        if (!process.waitForStarted()) {
            emit gameFinished(gameName, gameResult);
            qWarning() << "Failed to start game process for game:" << gameName;
            return;
        }

        if (!process.waitForFinished()) {
            emit gameFinished(gameName, gameResult);
            qWarning() << "Game process did not finish for game:" << gameName;
            return;
        }

        QString winner;
        QByteArray output = process.readAllStandardOutput();
        QByteArray errorOut = process.readAllStandardOutput();
        if (!errorOut.isEmpty()) {
            qDebug() << "Error occured while executing " << execPath << "\n" << errorOut;
        }
        QString outputText = QString(output).replace("\r\n", "\n").replace("\r", "\n");
        QStringList lines = outputText.split('\n', Qt::SkipEmptyParts);
        for (const QString &line : lines)
        {
            QString trimmedLine = line.trimmed();
            QRegularExpression winnerRegex(R"(WINNER:\s*([\w]+(?:,\s*[\w]+)?)$)");
            QRegularExpressionMatch match = winnerRegex.match(trimmedLine);
            if (match.hasMatch())
            {
                winner = match.captured(1);
            }
        }
        if (!winner.contains(','))
        {
            gameResult.winner = winner;
        }
        gameResult.success = true;
        emit gameFinished(gameName, gameResult);

    });

    thread->start();
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
}
