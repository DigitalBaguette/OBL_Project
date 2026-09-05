#ifndef PROMPTBUILDER_H
#define PROMPTBUILDER_H

#include <QString>
#include "../core/CompanyProfile.h"

/**
 * @class PromptBuilder
 * @brief Buduje sformatowaną treść zapytania (promptu) do modelu LLM na podstawie profilu firmy.
 */
class PromptBuilder {
public:
    /**
     * @brief Tworzy pełny, szczegółowy prompt sieciowy na podstawie danych firmy.
     * @param profile Profil firmy, dla której generowany jest prompt.
     * @return QString Gotowy tekst promptu, gotowy do wysłania do modelu LLM.
     */
    static QString buildNetworkPrompt(const CompanyProfile& profile);
};

#endif // PROMPTBUILDER_H