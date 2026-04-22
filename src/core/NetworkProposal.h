#ifndef NETWORKPROPOSAL_H
#define NETWORKPROPOSAL_H

#include <QString>
#include <QDateTime>

class NetworkProposal {
public:
    NetworkProposal() : timestamp(QDateTime::currentDateTime()) {}

    QString id;
    QString rawContent;      // Cała odpowiedź od AI
    QString structuredData;  // Przetworzone dane (JSON)
    QDateTime timestamp;
};

#endif