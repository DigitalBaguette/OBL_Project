#include "OllamaClient.h"
#include <QJsonDocument>
#include <QJsonObject>

OllamaClient::OllamaClient(QObject *parent) : QObject(parent) {
    networkManager = new QNetworkAccessManager(this);
}

void OllamaClient::sendRequest(const QString& prompt) {
    // Na razie pusta implementacja, żeby projekt ruszył
}

void OllamaClient::onReplyFinished(QNetworkReply* reply) {
    reply->deleteLater();
}