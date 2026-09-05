#include "JsonSerializer.h"
#include "../core/CompanyProfile.h"

QJsonObject JsonSerializer::serializeProfile(const CompanyProfile& profile) {
    QJsonObject obj;
    obj["industry"] = profile.industry;
    obj["employeeCount"] = profile.employeeCount;
    return obj;
}