#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../llm/OllamaClient.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ollama = new OllamaClient(this);

    connect(ollama, &OllamaClient::responseReceived, this, &MainWindow::handleAIResponse);
    connect(ollama, &OllamaClient::errorOccurred, this, &MainWindow::handleAIError);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::handleAIResponse(const QString& response) {
    QMessageBox::information(this, "Odpowiedź AI", response);
}

void MainWindow::handleAIError(const QString& error) {
    QMessageBox::critical(this, "Błąd", error);
}