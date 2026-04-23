#include "StatsView.h"
#include <QVBoxLayout>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

StatsView::StatsView(QWidget *parent) : QWidget(parent) {
    m_chartView = new QChartView(new QChart(), this);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_chartView);
}

void StatsView::updateStatistics(const QList<NetworkProposal>& history) {
    QChart *chart = m_chartView->chart();
    chart->removeAllSeries();

    QBarSeries *series = new QBarSeries();
    QBarSet *set = new QBarSet("Liczba pracowników");

    QStringList categories;
    int index = 1;

    for (const auto& project : history) {
        *set << project.profile.employeeCount;
        categories << QString("Proj %1").arg(index++);
    }

    series->append(set);
    chart->addSeries(series);
    chart->setTitle("Analiza wielkości projektowanych sieci");

    // Konfiguracja osi X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Konfiguracja osi Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Pracownicy");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
}