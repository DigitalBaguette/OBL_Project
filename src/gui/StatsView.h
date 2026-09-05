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

/**
 * @class StatsView
 * @brief Widok prezentujący wykres słupkowy liczby pracowników w zapisanych projektach.
 */
class StatsView : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor widoku statystyk.
     * @param parent Wskaźnik na widget nadrzędny.
     */
    explicit StatsView(QWidget *parent = nullptr);

    /**
     * @brief Odświeża wykres na podstawie historii projektów.
     * @param history Lista dotychczasowych propozycji.
     */
    void updateStatistics(const QList<NetworkProposal>& history);

private:
    QChartView *m_chartView;
};

#endif