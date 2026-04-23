/**
 * @file MainWindow.cpp
 * @brief Implementacja logiki głównego okna aplikacji.
 * * Plik zawiera definicje slotów obsługujących interakcję z użytkownikiem,
 * komunikację z silnikiem Ollama oraz asynchroniczne zapisywanie wyników do bazy.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../llm/OllamaClient.h"
#include "../llm/PromptBuilder.h"
#include "CompanyInputDialog.h"
#include "../core/NetworkProposal.h"
#include <QMessageBox>
#include <QUuid>
#include <QDateTime>

/**
 * @brief Inicjalizuje komponenty UI, klientów usług oraz nawiązuje połączenia sygnałów.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. Inicjalizacja modułów funkcjonalnych
    m_ollamaClient = new OllamaClient(this);
    m_dbManager = new DatabaseManager(this);

    // 2. Asynchroniczne przygotowanie bazy danych SQLite
    m_dbManager->initAsync("network_history.db");

    // 3. Połączenia sygnałów i slotów - Logika AI
    connect(m_ollamaClient, &OllamaClient::responseReceived,
            this, &MainWindow::handleAIResponse);
    connect(m_ollamaClient, &OllamaClient::errorOccurred,
            this, &MainWindow::handleAIError);

    // 4. Połączenia sygnałów - Warstwa danych
    connect(m_dbManager, &DatabaseManager::saveFinished,
            this, &MainWindow::onDatabaseOperationFinished);

    // Domyślnie przycisk wysyłki jest nieaktywny do czasu wygenerowania promptu
    ui->sendToAIButton->setEnabled(false);
}

/**
 * @brief Zwalnia zasoby interfejsu użytkownika.
 */
MainWindow::~MainWindow() {
    delete ui;
}

/**
 * @brief Otwiera dialog wejściowy i generuje prompt na podstawie danych firmy.
 */
void MainWindow::on_generateButton_clicked() {
    CompanyInputDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_currentProfile = dialog.getProfile();

        // Budowanie promptu przy użyciu wzorca Builder
        QString prompt = PromptBuilder::buildNetworkPrompt(m_currentProfile);

        ui->promptDisplay->setPlainText(prompt);
        ui->sendToAIButton->setEnabled(true);
    }
}

/**
 * @brief Przesyła treść promptu do lokalnego modelu AI (Ollama).
 */
void MainWindow::on_sendToAIButton_clicked() {
    QString content = ui->promptDisplay->toPlainText().trimmed();
    if (!content.isEmpty()) {
        ui->sendToAIButton->setEnabled(false);
        ui->promptDisplay->setPlainText("Trwa generowanie odpowiedzi przez AI...");
        m_ollamaClient->sendPrompt(content);
    }
}

/**
 * @brief Obsługuje poprawną odpowiedź z modelu i inicjuje proces zapisu.
 * @param response Tekst wygenerowany przez LLM.
 */
void MainWindow::handleAIResponse(const QString response) {
    ui->promptDisplay->setPlainText(response);
    ui->sendToAIButton->setEnabled(true);

    // Kapsułkowanie danych w obiekcie NetworkProposal
    NetworkProposal proposal;
    proposal.id = QUuid::createUuid().toString();
    proposal.timestamp = QDateTime::currentDateTime();
    proposal.rawContent = response;
    proposal.profile = m_currentProfile;

    // Zlecenie zapisu do bazy w osobnym wątku (Wymóg 6 - Wielowątkowość)
    m_dbManager->saveProposalAsync(proposal);
}

/**
 * @brief Wyświetla komunikat o błędzie w przypadku niepowodzenia komunikacji z AI.
 */
void MainWindow::handleAIError(const QString error) {
    QMessageBox::critical(this, "Błąd AI", "Nie udało się uzyskać odpowiedzi: " + error);
    ui->sendToAIButton->setEnabled(true);
}

/**
 * @brief Wyświetla status operacji zapisu na pasku stanu.
 */
void MainWindow::onDatabaseOperationFinished(bool success) {
    if (success) {
        statusBar()->showMessage("Projekt sieci został zapisany w historii (JSON/SQL).", 4000);
    } else {
        statusBar()->showMessage("Błąd krytyczny: Nie udało się zapisać danych!", 5000);
    }
}