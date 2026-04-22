#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CompanyInputDialog.h"
#include "../llm/PromptBuilder.h"
#include "../llm/OllamaClient.h"
#include <QMessageBox>

/**
 * @brief Konstruktor klasy MainWindow.
 * Inicjalizuje interfejs użytkownika oraz klienta LLM.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicjalizacja klienta Ollama
    m_ollamaClient = new OllamaClient(this);

    // Połączenie sygnałów klienta z funkcjami obsługi w oknie głównym
    connect(m_ollamaClient, &OllamaClient::responseReceived,
            this, &MainWindow::handleAIResponse);

    connect(m_ollamaClient, &OllamaClient::errorOccurred,
            this, &MainWindow::handleAIError);

    // Przycisk wysyłki jest domyślnie wyłączony do czasu wygenerowania promptu
    ui->sendToAIButton->setEnabled(false);
}

/**
 * @brief Destruktor klasy MainWindow.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Obsługa kliknięcia przycisku generowania profilu.
 */
void MainWindow::on_generateButton_clicked()
{
    CompanyInputDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted) {
        CompanyProfile profile = dialog.getProfile();
        QString prompt = PromptBuilder::buildNetworkPrompt(profile);

        ui->promptDisplay->setPlainText(prompt);
        ui->sendToAIButton->setEnabled(true);
    }
}

/**
 * @brief Wysyła treść widoczną w oknie do modelu AI.
 */
void MainWindow::on_sendToAIButton_clicked()
{
    QString content = ui->promptDisplay->toPlainText().trimmed();

    if (content.isEmpty()) return;

    ui->sendToAIButton->setEnabled(false);
    ui->promptDisplay->setPlainText("Łączenie z serwerem Ollama... Proszę czekać.");

    m_ollamaClient->sendPrompt(content);
}

/**
 * @brief Wyświetla odpowiedź otrzymaną od AI.
 */
void MainWindow::handleAIResponse(const QString &response)
{
    ui->promptDisplay->setPlainText(response);
    ui->sendToAIButton->setEnabled(true);
}

/**
 * @brief Obsługuje błędy komunikacji z AI.
 */
void MainWindow::handleAIError(const QString &error)
{
    QMessageBox::critical(this, "Błąd AI", error);
    ui->sendToAIButton->setEnabled(true);
}