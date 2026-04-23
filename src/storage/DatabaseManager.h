/**
 * @file DatabaseManager.h
 * @brief Zarządzanie warstwą trwałości danych w architekturze wielowątkowej.
 * @details Implementacja spełnia Wymóg 6 projektu poprzez odseparowanie operacji
 * wejścia/wyjścia (I/O) od głównego wątku GUI (Main Thread).
 */

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QThread>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "../core/NetworkProposal.h"

/**
 * @class DatabaseWorker
 * @brief Klasa wykonawcza (Worker) operująca bezpośrednio na sterowniku SQL.
 * @details Obiekt tej klasy jest przenoszony do osobnego wątku (QThread),
 * gdzie wykonuje blokujące operacje bazodanowe, komunikując się z managerem
 * wyłącznie poprzez system sygnałów i slotów.
 */
class DatabaseWorker : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor obiektu Worker.
     * @param parent Obiekt rodzica (zazwyczaj nullptr przy moveToThread).
     */
    explicit DatabaseWorker(QObject *parent = nullptr) : QObject(parent) {}

public slots:
    /**
     * @brief Inicjalizuje połączenie ze sterownikiem SQLite i tworzy schemat tabel.
     * @param dbName Ścieżka do pliku bazy danych.
     */
    void onInit(const QString &dbName);

    /**
     * @brief Zapisuje obiekt NetworkProposal w formacie zserializowanym.
     * @param proposal Obiekt propozycji do umieszczenia w bazie.
     */
    void onSave(const NetworkProposal &proposal);

    /**
     * @brief Pobiera wszystkie historyczne rekordy z bazy danych.
     */
    void onLoadAll();

signals:
    /**
     * @brief Sygnał emitowany po zakończeniu operacji zapisu lub inicjalizacji.
     * @param success Status powodzenia operacji.
     * @param message Komunikat błędu lub informacja o sukcesie.
     */
    void operationFinished(bool success, const QString &message);

    /**
     * @brief Emituje listę wczytanych obiektów propozycji.
     * @param proposals Lista obiektów NetworkProposal odtworzona z bazy.
     */
    void dataLoaded(const QList<NetworkProposal> &proposals);
};

/**
 * @class DatabaseManager
 * @brief Fasada zarządzająca cyklem życia wątku bazy danych.
 * @details Klasa ta pełni rolę wysokopoziomowego interfejsu dla GUI. Ukrywa
 * złożoność zarządzania wątkiem QThread i zapewnia bezpieczną wymianę danych
 * między wątkiem głównym a wątkiem bazy.
 */
class DatabaseManager : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Inicjalizuje managera i uruchamia wątek roboczy.
     */
    explicit DatabaseManager(QObject *parent = nullptr);

    /**
     * @brief Bezpiecznie zatrzymuje wątek i zwalnia zasoby.
     */
    ~DatabaseManager();

    /**
     * @brief Zleca asynchroniczną inicjalizację bazy danych.
     * @param dbName Nazwa pliku bazy.
     */
    void initAsync(const QString &dbName);

    /**
     * @brief Zleca asynchroniczny zapis propozycji.
     * @param proposal Dane do zapisania.
     */
    void saveProposalAsync(const NetworkProposal &proposal);

    /**
     * @brief Zleca asynchroniczne pobranie wszystkich danych.
     */
    void requestAllProposals();

signals:
    /** @name Sygnały sterujące Workerem (Wewnętrzne) */
    ///@{
    void initRequested(const QString &dbName);
    void saveRequested(const NetworkProposal &proposal);
    void loadRequested();
    ///@}

    /** @name Sygnały zwrotne dla GUI (Publiczne) */
    ///@{
    /**
     * @brief Emitowany, gdy proces zapisu został sfinalizowany.
     */
    void saveFinished(bool success);

    /**
     * @brief Emitowany, gdy historia została pomyślnie załadowana do pamięci RAM.
     */
    void allProposalsLoaded(const QList<NetworkProposal> &proposals);
    ///@}

private:
    QThread m_workerThread;         ///< Wątek systemowy, w którym pracuje DatabaseWorker.
    DatabaseWorker *m_worker;       ///< Obiekt wykonawczy zarządzany przez manager.
};

#endif // DATABASEMANAGER_H