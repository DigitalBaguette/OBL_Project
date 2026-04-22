#include "NetworkAnalyzer.h"

QString NetworkAnalyzer::preparePrompt(const CompanyProfile& profile) {
    return QString("Zaprojektuj sieć dla firmy z branży %1, posiadającej %2 pracowników.")
        .arg(profile.industry)
        .arg(profile.employeeCount);
}

bool NetworkAnalyzer::validateProposal(const NetworkProposal& proposal) {
    return !proposal.rawContent.isEmpty();
}