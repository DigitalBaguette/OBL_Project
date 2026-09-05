#include "NetworkResultWidget.h"
#include <QVBoxLayout>

NetworkResultWidget::NetworkResultWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);

    m_summaryLabel = new QLabel(this);
    m_summaryLabel->setWordWrap(true);
    m_summaryLabel->setStyleSheet("font-weight: bold;");

    m_contentBrowser = new QTextBrowser(this);
    m_contentBrowser->setReadOnly(true);

    layout->addWidget(m_summaryLabel);
    layout->addWidget(m_contentBrowser);
    setLayout(layout);
}

void NetworkResultWidget::displayProposal(const NetworkProposal &proposal) {
    QString summary = QString("Branża: %1 | Pracownicy: %2 | Lokalizacje: %3 | Priorytet: %4 | Data: %5")
                          .arg(proposal.profile.industry)
                          .arg(proposal.profile.employeeCount)
                          .arg(proposal.profile.locationsCount)
                          .arg(proposal.profile.priority)
                          .arg(proposal.timestamp.toString("yyyy-MM-dd hh:mm"));
    m_summaryLabel->setText(summary);
    m_contentBrowser->setPlainText(proposal.rawContent);
}