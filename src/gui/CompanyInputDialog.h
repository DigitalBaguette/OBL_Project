#ifndef COMPANYINPUTDIALOG_H
#define COMPANYINPUTDIALOG_H

#include <QDialog>
#include "../core/CompanyProfile.h"

namespace Ui { class CompanyInputDialog; }

class CompanyInputDialog : public QDialog {
    Q_OBJECT

public:
    explicit CompanyInputDialog(QWidget *parent = nullptr);
    ~CompanyInputDialog();
    CompanyProfile getProfile() const;

private:
    Ui::CompanyInputDialog *ui;
};

#endif