#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>

class HistoryWidget : public QWidget {
    Q_OBJECT
public:
    explicit HistoryWidget(QWidget *parent = nullptr);
    void addEntry(const QString& entry);

private:
    QListWidget* listWidget;
};

#endif