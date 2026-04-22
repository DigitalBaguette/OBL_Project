#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../core/CompanyProfile.h"

// Przestrzeń nazw dla wygenerowanego kodu UI
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Deklaracja wyprzedzająca klasy klienta AI (pozwala uniknąć problemów z AutoMoc)
class OllamaClient;

/**
 * @brief Klasa głównego okna aplikacji.
 * Zarządza interakcją użytkownika i komunikacją z modułem LLM.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    /**
     * @brief Slot obsługujący kliknięcie przycisku generowania promptu.
     */
    void on_generateButton_clicked();

    /**
     * @brief Slot przesyłający gotowy prompt do silnika AI.
     */
    void on_sendToAIButton_clicked();

    /**
     * @brief Odbiera tekstową odpowiedź z modelu AI.
     */
    void handleAIResponse(const QString &response);

    /**
     * @brief Obsługuje błędy zgłaszane przez klienta AI.
     */
    void handleAIError(const QString &error);

private:
    Ui::MainWindow *ui;            // Wskaźnik na elementy interfejsu użytkownika
    OllamaClient   *m_ollamaClient; // Wskaźnik na klienta API Ollama
};

#endif // MAINWINDOW_H