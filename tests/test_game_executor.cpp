#include "engine/game/game_executor.h"
#include "engine/game/game.h"
#include "app/config.h"
#include "engine/io/json_io_handler.h"
#include "test_config.h"
#include <QDebug>
#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QDir>
#include <string>

class TestGameExecutor final : public QObject
{
    Q_OBJECT

private slots:
    void testRunGameWithWinner();
    void testRunGameWithDraw();
};

void TestGameExecutor::testRunGameWithWinner()
{
    QString path = QDir::toNativeSeparators(QString(TEST_GAMES_DIR) + "/game.bat");
    Game mockGame("game", path);

    GameExecutor executor;
    QSignalSpy startedSpy(&executor, &GameExecutor::gameStarted);
    QSignalSpy finishedSpy(&executor, &GameExecutor::gameFinished);

    QMap<QString, QString> namedArgs = {{"player1", "Alice"}, {"player2", "Bob"}, {"winner", "Alice"}};
    executor.runGame(mockGame, namedArgs);

    QCOMPARE(startedSpy.count(), 1);
    QVERIFY(finishedSpy.wait(1000));

    QCOMPARE(finishedSpy.count(), 1);
    GameResult result = finishedSpy.takeFirst().at(1).value<GameResult>();

    QCOMPARE(result.success, true);
    QCOMPARE(result.winner, QString("Alice"));
}

void TestGameExecutor::testRunGameWithDraw()
{
    QString path = QDir::toNativeSeparators(QString(TEST_GAMES_DIR) + "/game.bat");
    Game mockGame("Mock Game", path);

    GameExecutor executor;
    QSignalSpy startedSpy(&executor, &GameExecutor::gameStarted);
    QSignalSpy finishedSpy(&executor, &GameExecutor::gameFinished);

    QMap<QString, QString> namedArgs = {{"player1", "Alice"}, {"player2", "Bob"}};
    executor.runGame(mockGame, namedArgs);

    QCOMPARE(startedSpy.count(), 1);
    QVERIFY(finishedSpy.wait(1000));

    QCOMPARE(finishedSpy.count(), 1);
    GameResult result = finishedSpy.takeFirst().at(1).value<GameResult>();

    QCOMPARE(result.success, true);
    QCOMPARE(result.winner, QString(""));
}

QTEST_MAIN(TestGameExecutor)
#include "test_game_executor.moc"
