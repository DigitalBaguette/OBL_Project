#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonObject>
#include <QString>

// Używamy forward declarations zamiast pełnych include,
// aby uniknąć błędu "nested too deeply"
class CompanyProfile;
class NetworkProposal;

class JsonSerializer {
public:
    static QJsonObject serializeProfile(const CompanyProfile& profile);
    static QJsonObject serializeProposal(const NetworkProposal& proposal);
    static NetworkProposal deserializeProposal(const QString& jsonStr);
};

#endif // JSONSERIALIZER_H