/**
 * @file DatabaseManager.cpp
 * @brief Implementacja asynchronicznego zarządcy bazy danych.
 */

#include "DatabaseManager.h"
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void DatabaseWorker::onInit(const QString &dbName) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "WorkerConnection");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        emit operationFinished(false, "Nie można otworzyć bazy: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    bool ok = query.exec("CREATE TABLE IF NOT EXISTS proposals ("
                         "id TEXT PRIMARY KEY, "
                         "timestamp TEXT, "
                         "json_data TEXT)");

    emit operationFinished(ok, ok ? "Baza zainicjalizowana" : query.lastError().text());
}

void DatabaseWorker::onSave(const NetworkProposal &proposal) {
    QSqlDatabase db = QSqlDatabase::database("WorkerConnection");
    QSqlQuery query(db);

    query.prepare("INSERT OR REPLACE INTO proposals (id, timestamp, json_data) VALUES (?, ?, ?)");
    query.addBindValue(proposal.id);
    query.addBindValue(proposal.timestamp.toString(Qt::ISODate));

    QJsonDocument doc(proposal.toJson());
    query.addBindValue(QString(doc.toJson(QJsonDocument::Compact)));

    if (query.exec()) {
        emit operationFinished(true, "Zapisano pomyślnie");
    } else {
        emit operationFinished(false, query.lastError().text());
    }
}

void DatabaseWorker::onLoadAll() {
    QSqlDatabase db = QSqlDatabase::database("WorkerConnection");
    QList<NetworkProposal> list;
    QSqlQuery query("SELECT json_data FROM proposals ORDER BY timestamp ASC", db);

    while (query.next()) {
        QJsonDocument doc = QJsonDocument::fromJson(query.value(0).toByteArray());
        if (!doc.isNull()) {
            list.append(NetworkProposal::fromJson(doc.object()));
        }
    }
    emit dataLoaded(list);
}

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent) {
    qRegisterMetaType<NetworkProposal>("NetworkProposal");
    qRegisterMetaType<QList<NetworkProposal>>("QList<NetworkProposal>");

    m_worker = new DatabaseWorker();
    m_worker->moveToThread(&m_workerThread);

    connect(&m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    connect(this, &DatabaseManager::initRequested, m_worker, &DatabaseWorker::onInit);
    connect(this, &DatabaseManager::saveRequested, m_worker, &DatabaseWorker::onSave);
    connect(this, &DatabaseManager::loadRequested, m_worker, &DatabaseWorker::onLoadAll);

    connect(m_worker, &DatabaseWorker::operationFinished, this, [this](bool success, const QString &msg){
        if(!success) {
            qDebug() << "DB Critical Error:" << msg;
        }
        emit saveFinished(success);
    });

    connect(m_worker, &DatabaseWorker::dataLoaded, this, &DatabaseManager::allProposalsLoaded);

    m_workerThread.start();
}

DatabaseManager::~DatabaseManager() {
    m_workerThread.quit();
    m_workerThread.wait();
}

void DatabaseManager::initAsync(const QString &dbName) { emit initRequested(dbName); }
void DatabaseManager::saveProposalAsync(const NetworkProposal &proposal) { emit saveRequested(proposal); }
void DatabaseManager::requestAllProposals() { emit loadRequested(); }