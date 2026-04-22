#include "HistoryWidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);
    setLayout(layout);
}

void HistoryWidget::addEntry(const QString& entry) {
    listWidget->addItem(entry);
}