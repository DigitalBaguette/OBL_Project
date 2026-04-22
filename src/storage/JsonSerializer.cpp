#include "JsonSerializer.h"
#include "../core/CompanyProfile.h"
#include "../core/NetworkProposal.h"
#include <QJsonDocument>

QJsonObject JsonSerializer::serializeProfile(const CompanyProfile& profile) {
    QJsonObject obj;
    obj["industry"] = profile.industry;
    obj["employeeCount"] = profile.employeeCount;
    // ... reszta pól
    return obj;
}

// ... reszta funkcji