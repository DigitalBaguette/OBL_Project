#include "HistoryWidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    layout->addWidget(listWidget);
    setLayout(layout);

    connect(listWidget, &QListWidget::itemDoubleClicked,
            this, &HistoryWidget::onItemDoubleClicked);
}

void HistoryWidget::setProposals(const QList<NetworkProposal> &proposals) {
    listWidget->clear();
    m_proposals = proposals;

    for (const auto &proposal : m_proposals) {
        QString entry = QString("[%1] %2 — %3 pracowników")
                            .arg(proposal.timestamp.toString("yyyy-MM-dd hh:mm"))
                            .arg(proposal.profile.industry)
                            .arg(proposal.profile.employeeCount);
        listWidget->addItem(entry);
    }
}

void HistoryWidget::onItemDoubleClicked(QListWidgetItem *item) {
    int index = listWidget->row(item);
    if (index >= 0 && index < m_proposals.size()) {
        emit proposalSelected(m_proposals.at(index));
    }
}