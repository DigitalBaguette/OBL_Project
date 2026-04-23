#include "TestAnalyzer.h"

void TestAnalyzer::testAverageEmployees() {
    QList<NetworkProposal> history;
    NetworkProposal p1; p1.profile.employeeCount = 10;
    NetworkProposal p2; p2.profile.employeeCount = 20;
    NetworkProposal p3; p3.profile.employeeCount = 60;
    history << p1 << p2 << p3;

    double result = NetworkAnalyzer::calculateAverageEmployees(history);
    QCOMPARE(result, 30.0);
}

void TestAnalyzer::testTrendDetection() {
    QList<NetworkProposal> history;
    NetworkProposal p1; p1.profile.employeeCount = 10;
    NetworkProposal p2; p2.profile.employeeCount = 50;
    history << p1 << p2;

    QString trend = NetworkAnalyzer::determineScaleTrend(history);
    QCOMPARE(trend, QString("Wzrostowy"));
}

void TestAnalyzer::testEmptyHistory() {
    QList<NetworkProposal> emptyHistory;
    double result = NetworkAnalyzer::calculateAverageEmployees(emptyHistory);
    QCOMPARE(result, 0.0);
    QString trend = NetworkAnalyzer::determineScaleTrend(emptyHistory);
    QCOMPARE(trend, QString("Brak danych"));
}

QTEST_MAIN(TestAnalyzer)