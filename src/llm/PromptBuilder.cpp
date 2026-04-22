#include "PromptBuilder.h"
#include <QStringList> // Potrzebne do obsługi profile.teams.join()

QString PromptBuilder::buildNetworkPrompt(const CompanyProfile& profile) {
    QString serverRoomStatus = profile.hasServerRoom ? "posiada wydzieloną serwerownię" : "nie posiada dedykowanej serwerowni (rozwiązania chmurowe lub szafy wiszące)";

    QString prompt = QString(
                         "Jesteś starszym architektem sieciowym. Przygotuj profesjonalny projekt infrastruktury IT.\n\n"
                         "=== DANE FIRMY ===\n"
                         "Branża: %1\n"
                         "Skala: %2 pracowników, %3 lokalizacji\n"
                         "Działy: %4\n"
                         "Infrastruktura: %5\n\n"
                         "=== WYMAGANIA PROJEKTOWE ===\n"
                         "Priorytet: %6\n"
                         "Budżet: %7\n"
                         "Dodatkowe uwagi: %8\n\n"
                         "=== OCZEKIWANA ODPOWIEDŹ ===\n"
                         "Proszę o: \n"
                         "1. Sugerowaną topologię sieci.\n"
                         "2. Listę niezbędnych urządzeń (routery, switche, AP).\n"
                         "3. Propozycję segmentacji (VLAN) dla wymienionych działów.\n"
                         "4. Rekomendacje dot. bezpieczeństwa zgodnie z priorytetem."
                         )
                         .arg(profile.industry)
                         .arg(profile.employeeCount)
                         .arg(profile.locationsCount)
                         .arg(profile.teams.join(", "))
                         .arg(serverRoomStatus)
                         .arg(profile.priority)
                         .arg(profile.budget)
                         .arg(profile.additionalNotes.isEmpty() ? "Brak" : profile.additionalNotes);

    return prompt;
}