#include "PromptBuilder.h"

QString PromptBuilder::buildNetworkPrompt(const CompanyProfile& profile) {
    return QString(
               "Jesteś ekspertem ds. sieci komputerowych. Zaprojektuj architekturę sieci dla firmy:\n"
               "Branża: %1\n"
               "Liczba pracowników: %2\n"
               "Liczba lokalizacji: %3\n"
               "Zespoły: %4\n\n"
               "Zaproponuj topologię, listę urządzeń (routery, switche, AP) oraz adresację IP."
               )
        .arg(profile.industry)
        .arg(profile.employeeCount)
        .arg(profile.locationsCount)
        .arg(profile.teams.join(", "));
}