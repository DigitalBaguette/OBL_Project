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
#include "HistoryWidget.h"
#include "StatsView.h"
#include "NetworkResultWidget.h"
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

    m_ollamaClient = new OllamaClient(this);
    m_dbManager = new DatabaseManager(this);

    m_historyWidget = new HistoryWidget();
    m_historyWidget->setWindowTitle("Historia projektów");
    m_historyWidget->resize(500, 400);

    m_statsView = new StatsView();
    m_statsView->setWindowTitle("Statystyki projektów");
    m_statsView->resize(600, 400);

    m_resultWidget = new NetworkResultWidget();
    m_resultWidget->setWindowTitle("Szczegóły propozycji");
    m_resultWidget->resize(600, 500);

    m_dbManager->initAsync("network_history.db");

    connect(m_ollamaClient, &OllamaClient::responseReceived,
            this, &MainWindow::handleAIResponse);
    connect(m_ollamaClient, &OllamaClient::errorOccurred,
            this, &MainWindow::handleAIError);

    connect(m_dbManager, &DatabaseManager::saveFinished,
            this, &MainWindow::onDatabaseOperationFinished);
    connect(m_dbManager, &DatabaseManager::allProposalsLoaded,
            this, &MainWindow::handleHistoryLoaded);

    connect(m_historyWidget, &HistoryWidget::proposalSelected,
            this, &MainWindow::handleProposalSelected);

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
 * @brief Zleca wczytanie historii z bazy i oznacza widok historii jako oczekujący na dane.
 */
void MainWindow::on_historyButton_clicked() {
    m_pendingHistoryAction = PendingHistoryAction::ShowHistory;
    m_dbManager->requestAllProposals();
}

/**
 * @brief Zleca wczytanie historii z bazy i oznacza widok statystyk jako oczekujący na dane.
 */
void MainWindow::on_statsButton_clicked() {
    m_pendingHistoryAction = PendingHistoryAction::ShowStats;
    m_dbManager->requestAllProposals();
}

/**
 * @brief Obsługuje poprawną odpowiedź z modelu i inicjuje proces zapisu.
 * @param response Tekst wygenerowany przez LLM.
 */
void MainWindow::handleAIResponse(const QString response) {
    ui->promptDisplay->setPlainText(response);
    ui->sendToAIButton->setEnabled(true);

    NetworkProposal proposal;
    proposal.id = QUuid::createUuid().toString();
    proposal.timestamp = QDateTime::currentDateTime();
    proposal.rawContent = response;
    proposal.profile = m_currentProfile;

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

/**
 * @brief Wypełnia oczekujący widok (historię lub statystyki) danymi z bazy i go wyświetla.
 * @param proposals Lista wszystkich zapisanych propozycji.
 */
void MainWindow::handleHistoryLoaded(const QList<NetworkProposal> &proposals) {
    switch (m_pendingHistoryAction) {
    case PendingHistoryAction::ShowHistory:
        m_historyWidget->setProposals(proposals);
        m_historyWidget->show();
        m_historyWidget->raise();
        break;
    case PendingHistoryAction::ShowStats:
        m_statsView->updateStatistics(proposals);
        m_statsView->show();
        m_statsView->raise();
        break;
    case PendingHistoryAction::None:
        break;
    }
    m_pendingHistoryAction = PendingHistoryAction::None;
}

/**
 * @brief Wypełnia widok szczegółów wybraną propozycją i go wyświetla.
 * @param proposal Propozycja wybrana przez użytkownika w oknie historii.
 */
void MainWindow::handleProposalSelected(const NetworkProposal &proposal) {
    m_resultWidget->displayProposal(proposal);
    m_resultWidget->show();
    m_resultWidget->raise();
}