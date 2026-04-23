#include "NetworkAnalyzer.h"
#include <numeric>
#include <algorithm>

// Twoja obecna metoda (rozbudowana pod lepszy prompt)
QString NetworkAnalyzer::preparePrompt(const CompanyProfile& profile) {
    return QString("Jako ekspert IT, zaprojektuj sieć dla firmy z branży %1. "
                   "Dane: %2 pracowników, %3 lokalizacji. Priorytet: %4.")
        .arg(profile.industry)
        .arg(profile.employeeCount)
        .arg(profile.locationsCount)
        .arg(profile.priority);
}

bool NetworkAnalyzer::validateProposal(const NetworkProposal& proposal) {
    return !proposal.rawContent.isEmpty();
}

// Implementacja wymogów analizy [cite: 57, 59, 60]
double NetworkAnalyzer::calculateAverageEmployees(const QList<NetworkProposal>& history) {
    if (history.isEmpty()) return 0.0;
    int sum = 0;
    for(const auto& p : history) sum += p.profile.employeeCount;
    return static_cast<double>(sum) / history.size(); // [cite: 59]
}

NetworkProposal NetworkAnalyzer::findExtensiveProject(const QList<NetworkProposal>& history) {
    if (history.isEmpty()) return NetworkProposal();
    return *std::max_element(history.begin(), history.end(),
                             [](const NetworkProposal& a, const NetworkProposal& b) {
                                 return a.profile.locationsCount < b.profile.locationsCount;
                             }); // [cite: 57, 58]
}

QString NetworkAnalyzer::determineScaleTrend(const QList<NetworkProposal>& history) {
    if (history.size() < 2) return "Stabilny (mało danych)";
    int delta = history.last().profile.employeeCount - history.first().profile.employeeCount;
    return (delta > 0) ? "Wzrostowy" : "Spadkowy"; // [cite: 60]
}