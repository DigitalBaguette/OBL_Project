/**
 * @file MainWindow.h
 * @brief Deklaracja głównego okna aplikacji projektującej sieci AI.
 * @author Twój Numer Indeksu / Imię i Nazwisko
 * @date 2026
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "../core/CompanyProfile.h"
#include "../storage/DatabaseManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class OllamaClient;
class HistoryWidget;
class StatsView;
class NetworkResultWidget;

/**
 * @class MainWindow
 * @brief Klasa zarządzająca głównym interfejsem użytkownika.
 * * MainWindow pełni rolę kontrolera pośredniczącego między interfejsem (UI),
 * klientem sztucznej inteligencji (OllamaClient) oraz warstwą trwałości danych (DatabaseManager).
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor klasy MainWindow.
     * @param parent Wskaźnik na obiekt rodzica (domyślnie nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Wirtualny destruktor klasy MainWindow.
     */
    virtual ~MainWindow();

private slots:
    /**
     * @brief Slot obsługujący zdarzenie kliknięcia przycisku generowania profilu.
     */
    void on_generateButton_clicked();

    /**
     * @brief Slot wysyłający przygotowany prompt do modelu LLM.
     */
    void on_sendToAIButton_clicked();

    /**
     * @brief Slot obsługujący kliknięcie przycisku pokazującego historię projektów.
     */
    void on_historyButton_clicked();

    /**
     * @brief Slot obsługujący kliknięcie przycisku pokazującego statystyki projektów.
     */
    void on_statsButton_clicked();

    /**
     * @brief Przetwarza tekstową odpowiedź otrzymaną z silnika AI.
     * @param response Treść odpowiedzi wygenerowanej przez AI.
     */
    void handleAIResponse(const QString response);

    /**
     * @brief Obsługuje błędy komunikacji z serwerem Ollama.
     * @param error Komunikat błędu do wyświetlenia użytkownikowi.
     */
    void handleAIError(const QString error);

    /**
     * @brief Informuje o statusie zakończenia operacji na bazie danych.
     * @param success Prawda, jeśli operacja (np. zapis JSON) zakończyła się sukcesem.
     */
    void onDatabaseOperationFinished(bool success);

    /**
     * @brief Odbiera pełną historię propozycji wczytaną z bazy danych i przekazuje ją
     * do aktualnie oczekującego widoku (historii lub statystyk).
     * @param proposals Lista wszystkich zapisanych propozycji.
     */
    void handleHistoryLoaded(const QList<NetworkProposal> &proposals);

    /**
     * @brief Otwiera podgląd pełnej treści wybranej propozycji z historii.
     * @param proposal Propozycja wybrana przez użytkownika.
     */
    void handleProposalSelected(const NetworkProposal &proposal);

private:
    /**
     * @enum PendingHistoryAction
     * @brief Określa, który widok ma zostać wypełniony po wczytaniu historii z bazy.
     */
    enum class PendingHistoryAction { None, ShowHistory, ShowStats };

    Ui::MainWindow *ui;               ///< Wskaźnik na interfejs użytkownika wygenerowany z pliku .ui.
    OllamaClient   *m_ollamaClient;    ///< Klient odpowiedzialny za komunikację z API LLM.
    DatabaseManager *m_dbManager;      ///< Manager zarządzający asynchronicznym zapisem do bazy SQLite/JSON.
    CompanyProfile  m_currentProfile;  ///< Przechowuje dane aktualnie przetwarzanego profilu firmy.
    HistoryWidget   *m_historyWidget;  ///< Okno prezentujące historię zapisanych propozycji.
    StatsView       *m_statsView;      ///< Okno prezentujące statystyki zapisanych propozycji.
    NetworkResultWidget *m_resultWidget; ///< Okno prezentujące pełną treść wybranej propozycji.
    PendingHistoryAction m_pendingHistoryAction = PendingHistoryAction::None; ///< Widok oczekujący na dane z bazy.
};

#endif // MAINWINDOW_H