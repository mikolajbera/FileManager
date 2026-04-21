/**
 * @file mainwindow.h
 * @brief Definicja klasy głównego okna z obsługą sieci i AI.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @class MainWindow
 * @brief Klasa zarządzająca interfejsem i komunikacją z modelem Ollama.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief Statyczna funkcja czyszcząca surowy kod z odpowiedzi AI.
     * @param rawCode Tekst otrzymany bezpośrednio z API.
     * @return Oczyszczony kod Python gotowy do zapisu.
     */
    static QString cleanAiResponse(const QString &rawCode);

private slots:
    void on_btnBrowse_clicked();
    void on_btnExecute_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
};
#endif // MAINWINDOW_H