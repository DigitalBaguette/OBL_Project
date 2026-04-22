#include "DatabaseManager.h"
#include <QDebug>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager inst;
    return inst;
}

bool DatabaseManager::init(const QString& dbName) {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(dbName);

    if (!m_db.open()) {
        qDebug() << "Błąd otwierania bazy danych:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query;
    return query.exec("CREATE TABLE IF NOT EXISTS proposals ("
                      "id TEXT PRIMARY KEY, "
                      "content TEXT, "
                      "timestamp DATETIME)");
}

bool DatabaseManager::saveProposal(const NetworkProposal& proposal) {
    QSqlQuery query;
    query.prepare("INSERT INTO proposals (id, content, timestamp) VALUES (?, ?, ?)");
    query.addBindValue(proposal.id);
    query.addBindValue(proposal.rawContent);
    query.addBindValue(proposal.timestamp);
    return query.exec();
}