#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include "../core/NetworkProposal.h"

/**
 * @class HistoryWidget
 * @brief Widok listy historycznych propozycji sieci zapisanych w bazie danych.
 */
class HistoryWidget : public QWidget {
    Q_OBJECT
public:
    /**
     * @brief Konstruktor widgetu historii.
     * @param parent Wskaźnik na widget nadrzędny.
     */
    explicit HistoryWidget(QWidget *parent = nullptr);

    /**
     * @brief Wypełnia listę historii podanymi propozycjami, zastępując poprzednią zawartość.
     * @param proposals Lista propozycji do wyświetlenia.
     */
    void setProposals(const QList<NetworkProposal> &proposals);

signals:
    /**
     * @brief Emitowany po dwukrotnym kliknięciu wpisu historii.
     * @param proposal Wybrana propozycja sieci.
     */
    void proposalSelected(const NetworkProposal &proposal);

private slots:
    /**
     * @brief Emituje proposalSelected dla propozycji odpowiadającej klikniętemu elementowi.
     * @param item Kliknięty element listy.
     */
    void onItemDoubleClicked(QListWidgetItem *item);

private:
    QListWidget* listWidget;
    QList<NetworkProposal> m_proposals;
};

#endif