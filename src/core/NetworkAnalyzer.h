/**
 * @file NetworkAnalyzer.h
 * @brief Klasa odpowiedzialna za analizę statystyczną i przygotowanie danych dla AI.
 */
#ifndef NETWORKANALYZER_H
#define NETWORKANALYZER_H

#include <QString>
#include <QList>
#include "../core/CompanyProfile.h"
#include "../core/NetworkProposal.h"

class NetworkAnalyzer {
public:
    // Istniejące metody (zostawiamy lub lekko modyfikujemy)
    static QString preparePrompt(const CompanyProfile& profile);
    static bool validateProposal(const NetworkProposal& proposal);

    // NOWE METODY ANALITYCZNE (Wymóg: Prosta analiza danych )

    /**
     * @brief Oblicza średnią liczbę pracowników w zapisanych projektach[cite: 59].
     */
    static double calculateAverageEmployees(const QList<NetworkProposal>& history);

    /**
     * @brief Znajduje projekt z największą infrastrukturą (max lokalizacji)[cite: 57].
     */
    static NetworkProposal findExtensiveProject(const QList<NetworkProposal>& history);

    /**
     * @brief Określa trend wielkości projektów (czy firmy rosną)[cite: 60].
     */
    static QString determineScaleTrend(const QList<NetworkProposal>& history);
};

#endif