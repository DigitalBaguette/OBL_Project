#ifndef PROMPTBUILDER_H
#define PROMPTBUILDER_H

#include <QString>
#include "../core/CompanyProfile.h" // Poprawiona ścieżka relatywna

class PromptBuilder {
public:
    static QString buildNetworkPrompt(const CompanyProfile& profile);
};

#endif