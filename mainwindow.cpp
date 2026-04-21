#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QJsonObject>
#include <QJsonDocument>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    networkManager = new QNetworkAccessManager(this);
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::cleanAiResponse(const QString &rawCode) {
    QString code = rawCode;
    // Usuwamy bloki markdowna i zbędne spacje
    return code.remove("```python").remove("```").trimmed();
}

void MainWindow::on_btnBrowse_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, "Wybierz folder", "C://");
    if (!dir.isEmpty()) {
        ui->txtPath->setText(dir);
    }
}

void MainWindow::on_btnExecute_clicked() {
    QString path = ui->txtPath->text();
    QString instruction = ui->txtInstruction->text();

    if (path.isEmpty() || instruction.isEmpty()) {
        ui->txtLog->append("Błąd: Ścieżka i instrukcja nie mogą być puste.");
        return;
    }

    ui->progressBar->setVisible(true);
    ui->progressBar->setRange(0, 0);
    ui->txtLog->append("Wysyłam zapytanie do modelu...");

    QUrl url("http://localhost:11434/api/generate");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["model"] = "llama3";
    json["stream"] = false;
    json["system"] = "Jesteś ekspertem automatyzacji plików w Pythonie. "
                     "Zwracaj TYLKO czysty kod Python bez żadnych wyjaśnień i znaczników markdown. "
                     "Skrypt musi działać w folderze podanym w promptcie.";
    json["prompt"] = QString("Folder: %1\nZadanie: %2").arg(path, instruction);

    QJsonDocument doc(json);
    QNetworkReply *reply = networkManager->post(request, doc.toJson());

    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        ui->progressBar->setVisible(false);

        if (reply->error() == QNetworkReply::NoError) {
            QJsonDocument responseDoc = QJsonDocument::fromJson(reply->readAll());
            QString rawResponse = responseDoc.object().value("response").toString();

            // Użycie naszej statycznej funkcji (którą testujemy)
            QString code = MainWindow::cleanAiResponse(rawResponse);

            ui->txtLog->append("--- WYGENEROWANY KOD ---");
            ui->txtLog->append(code);
            ui->txtLog->append("------------------------");

            QString scriptPath = QDir::currentPath() + "/generated_script.py";
            QFile file(scriptPath);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&file);
                out << code;
                file.close();

                QProcess *process = new QProcess(this);
                process->start("python", QStringList() << scriptPath);

                connect(process, &QProcess::finished, this, [this, process]() {
                    ui->txtLog->append("Zadanie zakończone.");
                    QString output = process->readAllStandardOutput().trimmed();
                    QString error = process->readAllStandardError().trimmed();

                    if (!output.isEmpty()) ui->txtLog->append("Wynik:\n" + output);
                    if (!error.isEmpty()) ui->txtLog->append("BŁĄD SKRYPTU:\n" + error);
                    process->deleteLater();
                });
            }
        } else {
            ui->txtLog->append("BŁĄD POŁĄCZENIA: " + reply->errorString());
        }
        reply->deleteLater();
    });
}