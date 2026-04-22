#include "CompanyInputDialog.h"
#include "ui_CompanyInputDialog.h"
#include "../core/CompanyProfile.h"

// 1. KONSTRUKTOR - tego prawdopodobnie brakuje
CompanyInputDialog::CompanyInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompanyInputDialog)
{
    ui->setupUi(this);
}

// 2. DESTRUKTOR - tego też prawdopodobnie brakuje
CompanyInputDialog::~CompanyInputDialog()
{
    delete ui;
}

// 3. TWOJA FUNKCJA
CompanyProfile CompanyInputDialog::getProfile() const {
    CompanyProfile profile;
    // ... tutaj reszta Twojego kodu pobierającego dane ...
    profile.industry = ui->industryLineEdit->text();
    profile.employeeCount = ui->employeeSpinBox->value();
    profile.locationsCount = ui->locationsSpinBox->value();
    profile.teams = ui->teamsLineEdit->text().split(',', Qt::SkipEmptyParts);
    for(QString &team : profile.teams) team = team.trimmed();
    profile.priority = ui->priorityComboBox->currentText();
    profile.budget = ui->budgetComboBox->currentText();
    profile.hasServerRoom = ui->serverRoomCheckBox->isChecked();

    // Jeśli masz Plain Text Edit, użyj toPlainText(), jeśli Line Edit - text()
    profile.additionalNotes = ui->additionalNotesEdit->toPlainText();

    return profile;
}