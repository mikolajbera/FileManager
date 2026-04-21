#include <QtTest>
#include "mainwindow.h"

class TestCleaner : public QObject {
    Q_OBJECT

private slots:
    void testCleanWithTags() {
        QString input = "```python\nprint('test')\n```";
        QString expected = "print('test')";
        QCOMPARE(MainWindow::cleanAiResponse(input), expected);
    }

    void testCleanAlreadyClean() {
        QString input = "import os";
        QCOMPARE(MainWindow::cleanAiResponse(input), input);
    }
};

QTEST_MAIN(TestCleaner)
#include "test_cleaner.moc"