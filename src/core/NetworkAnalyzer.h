#ifndef NETWORKANALYZER_H
#define NETWORKANALYZER_H

#include <QString>
#include "CompanyProfile.h"
#include "NetworkProposal.h"

class NetworkAnalyzer {
public:
    NetworkAnalyzer() = default;

    // Funkcja do przygotowania promptu dla AI
    QString preparePrompt(const CompanyProfile& profile);

    // Funkcja do wstępnej weryfikacji propozycji
    bool validateProposal(const NetworkProposal& proposal);
};

#endif