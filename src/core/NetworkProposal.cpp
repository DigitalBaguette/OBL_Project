/**
 * @file NetworkProposal.cpp
 * @brief Implementacja metod serializacji do formatu JSON dla klasy NetworkProposal.
 */
#include "NetworkProposal.h"

QJsonObject NetworkProposal::toJson() const {
    QJsonObject root;
    root["id"] = id;
    root["timestamp"] = timestamp.toString(Qt::ISODate);
    root["content"] = rawContent;

    // Zagnieżdżamy profil firmy jako osobny obiekt wewnątrz JSON
    QJsonObject profileObj;
    profileObj["industry"] = profile.industry;
    profileObj["employees"] = profile.employeeCount;
    profileObj["locations"] = profile.locationsCount;
    profileObj["priority"] = profile.priority;

    root["profile"] = profileObj;
    return root;
}

NetworkProposal NetworkProposal::fromJson(const QJsonObject &json) {
    NetworkProposal p;
    p.id = json["id"].toString();
    p.timestamp = QDateTime::fromString(json["timestamp"].toString(), Qt::ISODate);
    p.rawContent = json["content"].toString();

    if (json.contains("profile")) {
        QJsonObject profObj = json["profile"].toObject();
        p.profile.industry = profObj["industry"].toString();
        p.profile.employeeCount = profObj["employees"].toInt();
        p.profile.locationsCount = profObj["locations"].toInt();
        p.profile.priority = profObj["priority"].toString();
    }

    return p;
}