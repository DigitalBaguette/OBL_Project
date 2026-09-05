#ifndef TESTANALYZER_H
#define TESTANALYZER_H

#include <QtTest>
#include "../src/core/NetworkAnalyzer.h"
#include "../src/core/NetworkProposal.h"

/**
 * @class TestAnalyzer
 * @brief Testy jednostkowe klasy NetworkAnalyzer, weryfikujące logikę analityczną bez uruchamiania GUI.
 */
class TestAnalyzer : public QObject {
    Q_OBJECT
private slots:
    /**
     * @brief Weryfikuje poprawność obliczania średniej liczby pracowników w historii projektów.
     */
    void testAverageEmployees();

    /**
     * @brief Weryfikuje poprawność wykrywania trendu wzrostowego w historii projektów.
     */
    void testTrendDetection();

    /**
     * @brief Weryfikuje zachowanie metod analitycznych dla pustej historii projektów.
     */
    void testEmptyHistory();
};

#endif