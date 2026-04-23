#include <QtTest>
#include "../src/core/NetworkAnalyzer.h"
#include "../src/core/NetworkProposal.h"

/**
 * @class TestAnalyzer
 * @brief Klasa testowa do weryfikacji modułu analitycznego.
 */
class TestAnalyzer : public QObject {
    Q_OBJECT

private slots:
    /**
     * @brief Testuje obliczanie średniej liczby pracowników.
     */
    void testAverageEmployees() {
        QList<NetworkProposal> history;

        // Przygotowanie danych testowych
        NetworkProposal p1; p1.profile.employeeCount = 10;
        NetworkProposal p2; p2.profile.employeeCount = 20;
        NetworkProposal p3; p3.profile.employeeCount = 60;

        history << p1 << p2 << p3;

        // Oczekiwana średnia: (10 + 20 + 60) / 3 = 30
        double result = NetworkAnalyzer::calculateAverageEmployees(history);
        
        QCOMPARE(result, 30.0);
    }

    /**
     * @brief Testuje wykrywanie trendu wzrostowego.
     */
    void testTrendDetection() {
        QList<NetworkProposal> history;
        
        NetworkProposal p1; p1.profile.employeeCount = 10;
        NetworkProposal p2; p2.profile.employeeCount = 50; // Wzrost

        history << p1 << p2;

        QString trend = NetworkAnalyzer::determineScaleTrend(history);
        QCOMPARE(trend, QString("Wzrostowy"));
    }
};

QTEST_MAIN(TestAnalyzer)
#include "TestAnalyzer.moc"