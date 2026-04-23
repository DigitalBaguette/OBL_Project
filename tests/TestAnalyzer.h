#ifndef TESTANALYZER_H
#define TESTANALYZER_H

#include <QtTest>
#include "../src/core/NetworkAnalyzer.h"
#include "../src/core/NetworkProposal.h"

class TestAnalyzer : public QObject {
    Q_OBJECT
private slots:
    void testAverageEmployees();
    void testTrendDetection();
    void testEmptyHistory();
};

#endif