#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include "../core/NetworkProposal.h"

/**
 * @brief Klasa zarządzająca bazą danych SQLite.
 * Używa wzorca Singleton, aby zapewnić jeden punkt dostępu do bazy.
 */
class DatabaseManager {
public:
    // Pobranie instancji managera
    static DatabaseManager& instance();

    // Inicjalizacja bazy danych (tworzenie pliku i tabel)
    bool init(const QString& dbName = "network_data.db");

    // Zapisywanie propozycji sieci do bazy
    bool saveProposal(const NetworkProposal& proposal);

    // Zapobieganie kopiowaniu obiektu (zasada Singleton)
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

private:
    // Prywatny konstruktor
    DatabaseManager() = default;

    QSqlDatabase m_db;
};

#endif // DATABASEMANAGER_H