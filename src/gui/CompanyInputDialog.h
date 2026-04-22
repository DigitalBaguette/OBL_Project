#ifndef COMPANYINPUTDIALOG_H
#define COMPANYINPUTDIALOG_H

#include <QDialog>
#include "../core/CompanyProfile.h" // Kluczowe!

namespace Ui {
class CompanyInputDialog;
}

class CompanyInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CompanyInputDialog(QWidget *parent = nullptr);
    ~CompanyInputDialog();

    // Deklaracja metody, którą implementujemy w .cpp
    CompanyProfile getProfile() const;

private:
    Ui::CompanyInputDialog *ui;
};

#endif // COMPANYINPUTDIALOG_H