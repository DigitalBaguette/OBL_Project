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

/**
 * @class NetworkAnalyzer
 * @brief Zbiór statycznych metod do budowy promptów oraz analizy historii projektów sieciowych.
 */
class NetworkAnalyzer {
public:
    /**
     * @brief Buduje treść zapytania (promptu) do modelu LLM na podstawie profilu firmy.
     * @param profile Profil firmy, dla której generowany jest prompt.
     * @return QString Gotowy tekst promptu.
     */
    static QString preparePrompt(const CompanyProfile& profile);

    /**
     * @brief Sprawdza, czy propozycja sieci zawiera treść wygenerowaną przez AI.
     * @param proposal Propozycja do walidacji.
     * @return bool True, jeśli propozycja nie jest pusta.
     */
    static bool validateProposal(const NetworkProposal& proposal);

    /**
     * @brief Oblicza średnią liczbę pracowników w zapisanych projektach[cite: 59].
     * @param history Lista dotychczasowych propozycji.
     * @return double Średnia liczba pracowników, 0.0 dla pustej historii.
     */
    static double calculateAverageEmployees(const QList<NetworkProposal>& history);

    /**
     * @brief Znajduje projekt z największą infrastrukturą (max lokalizacji)[cite: 57].
     * @param history Lista dotychczasowych propozycji.
     * @return NetworkProposal Projekt z największą liczbą lokalizacji, pusty obiekt dla pustej historii.
     */
    static NetworkProposal findExtensiveProject(const QList<NetworkProposal>& history);

    /**
     * @brief Określa trend wielkości projektów (czy firmy rosną)[cite: 60].
     * @param history Lista dotychczasowych propozycji.
     * @return QString Opis trendu: "Brak danych", "Stabilny (mało danych)", "Wzrostowy" lub "Spadkowy".
     */
    static QString determineScaleTrend(const QList<NetworkProposal>& history);
};

#endif