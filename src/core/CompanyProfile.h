#ifndef COMPANYPROFILE_H
#define COMPANYPROFILE_H

#include <QString>
#include <QStringList>

struct CompanyProfile {
    QString industry;
    int employeeCount;
    int locationsCount;
    QStringList teams;
    QString priority;
    QString budget;
    bool hasServerRoom;    // Dla CheckBoxa
    QString additionalNotes;
};

#endif // COMPANYPROFILE_H