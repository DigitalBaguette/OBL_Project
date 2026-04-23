/**
 * @file StatsView.h
 * @brief Klasa odpowiedzialna za wizualizację statystyk (Wymóg 4).
 */
#ifndef STATSVIEW_H
#define STATSVIEW_H

#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include "../core/NetworkProposal.h"

class StatsView : public QWidget {
    Q_OBJECT
public:
    explicit StatsView(QWidget *parent = nullptr);

    /**
     * @brief Odświeża wykres na podstawie historii projektów.
     */
    void updateStatistics(const QList<NetworkProposal>& history);

private:
    QChartView *m_chartView;
};

#endif