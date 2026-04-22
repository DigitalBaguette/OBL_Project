#include "CompanyInputDialog.h"
#include "ui_CompanyInputDialog.h"

CompanyInputDialog::CompanyInputDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::CompanyInputDialog) {
    ui->setupUi(this);
}

CompanyInputDialog::~CompanyInputDialog() {
    delete ui;
}

CompanyProfile CompanyInputDialog::getProfile() const {
    CompanyProfile profile;
    profile.industry = ui->industryEdit->text();
    profile.employeeCount = ui->employeeSpin->value();
    return profile;
}