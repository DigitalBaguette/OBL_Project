#ifndef COMPANYPROFILE_H
#define COMPANYPROFILE_H

#include <QString>
#include <QStringList>

class CompanyProfile {
public:
    QString industry;        // Branża firmy
    int employeeCount = 0;   // Liczba pracowników
    QStringList teams;       // Lista działów/zespołów
    int locationsCount = 1;  // Liczba lokalizacji
};

#endif