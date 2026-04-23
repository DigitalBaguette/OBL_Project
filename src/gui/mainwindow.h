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

// Deklaracja wyprzedzająca w celu skrócenia czasu kompilacji
class OllamaClient;

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
     * Inicjalizuje komponenty UI, klienta AI oraz wątek bazy danych.
     * @param parent Wskaźnik na obiekt rodzica (domyślnie nullptr).
     */
    MainWindow(QWidget *parent = nullptr);

    /**
     * @brief Wirtualny destruktor klasy MainWindow.
     * Zapewnia poprawne zwolnienie zasobów i bezpieczne zamknięcie wątków.
     */
    virtual ~MainWindow();

private slots:
    /**
     * @brief Slot obsługujący zdarzenie kliknięcia przycisku generowania profilu.
     * Wyświetla okno dialogowe wejścia danych firmy.
     */
    void on_generateButton_clicked();

    /**
     * @brief Slot wysyłający przygotowany prompt do modelu LLM.
     */
    void on_sendToAIButton_clicked();

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

private:
    Ui::MainWindow *ui;               ///< Wskaźnik na interfejs użytkownika wygenerowany z pliku .ui.
    OllamaClient   *m_ollamaClient;    ///< Klient odpowiedzialny za komunikację z API LLM.
    DatabaseManager *m_dbManager;      ///< Manager zarządzający asynchronicznym zapisem do bazy SQLite/JSON.
    CompanyProfile  m_currentProfile;  ///< Przechowuje dane aktualnie przetwarzanego profilu firmy.
};

#endif // MAINWINDOW_H