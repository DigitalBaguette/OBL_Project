/**
 * @file NetworkProposal.h
 * @brief Klasa reprezentująca wygenerowaną propozycję sieciową.
 */
#ifndef NETWORKPROPOSAL_H
#define NETWORKPROPOSAL_H

#include <QString>
#include <QDateTime>
#include "CompanyProfile.h"

/**
 * @brief Klasa przechowująca dane o propozycji sieciowej oraz odpowiedzi AI.
 * Służy jako kontener danych dla bazy danych JSON.
 */
class NetworkProposal {
public:
    NetworkProposal() = default;

    /**
     * @brief Pełna treść odpowiedzi wygenerowanej przez LLM.
     */
    QString rawContent;

    /**
     * @brief Profil firmy, na podstawie którego wygenerowano propozycję.
     */
    CompanyProfile profile;

    /**
     * @brief Data i godzina utworzenia propozycji.
     */
    QDateTime timestamp;

    /**
     * @brief Unikalny identyfikator propozycji (potrzebny do bazy danych).
     */
    QString id;
};

#endif // NETWORKPROPOSAL_H