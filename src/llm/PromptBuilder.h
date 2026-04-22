#ifndef PROMPTBUILDER_H
#define PROMPTBUILDER_H

#include <QString>
#include "../core/CompanyProfile.h" // Ścieżka musi wyjść z llm i wejść do core

class PromptBuilder {
public:
    static QString buildNetworkPrompt(const CompanyProfile& profile);
};

#endif // PROMPTBUILDER_H