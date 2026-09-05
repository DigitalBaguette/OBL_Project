#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonObject>

class CompanyProfile;

/**
 * @class JsonSerializer
 * @brief Pomocnicze metody serializacji obiektów domenowych do formatu JSON.
 */
class JsonSerializer {
public:
    /**
     * @brief Serializuje profil firmy do obiektu JSON.
     * @param profile Profil firmy do zserializowania.
     * @return QJsonObject Reprezentacja profilu w formacie klucz-wartość.
     */
    static QJsonObject serializeProfile(const CompanyProfile& profile);
};

#endif // JSONSERIALIZER_H