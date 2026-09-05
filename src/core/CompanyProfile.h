#ifndef COMPANYPROFILE_H
#define COMPANYPROFILE_H

#include <QString>
#include <QStringList>

/**
 * @struct CompanyProfile
 * @brief Dane wejściowe opisujące profil firmy klienta, zbierane w formularzu.
 */
struct CompanyProfile {
    QString industry;          ///< Branża, w której działa firma.
    int employeeCount;         ///< Liczba pracowników zatrudnionych w firmie.
    int locationsCount;        ///< Liczba lokalizacji/budynków firmy.
    QStringList teams;         ///< Lista działów/zespołów funkcjonujących w firmie.
    QString priority;          ///< Priorytet projektowanej sieci (bezpieczeństwo/wydajność/koszty).
    QString budget;            ///< Standard budżetowy planowanej sieci.
    bool hasServerRoom;        ///< True, jeśli firma posiada dedykowaną serwerownię.
    QString additionalNotes;   ///< Dodatkowe uwagi wpisane przez użytkownika.
};

#endif // COMPANYPROFILE_H