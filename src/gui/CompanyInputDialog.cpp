#include "CompanyInputDialog.h"
#include "ui_CompanyInputDialog.h"

/**
 * @brief Konstruktor okna dialogowego.
 * Inicjalizuje interfejs użytkownika oraz łączy przyciski systemowe z logiką okna.
 */
CompanyInputDialog::CompanyInputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompanyInputDialog)
{
    ui->setupUi(this);
    ui->employeeSpinBox->setRange(1, 10000);
    ui->locationsSpinBox->setRange(1, 100);
    // Połączenie przycisków OK i Anuluj z mechanizmami zamykania okna
    // Bez tych linii okno nie zareaguje na kliknięcie przycisków w ButtonBox
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

/**
 * @brief Destruktor klasy. Zwalnia pamięć zarezerwowaną dla interfejsu.
 */
CompanyInputDialog::~CompanyInputDialog()
{
    delete ui;
}

/**
 * @brief Pobiera dane z pól formularza i pakuje je w strukturę CompanyProfile.
 * @return Wypełniony obiekt profilu firmy, gotowy do przekazania do PromptBuildera.
 */
CompanyProfile CompanyInputDialog::getProfile() const
{
    CompanyProfile profile;

    // Pobieranie tekstów i wartości numerycznych z widgetów zdefiniowanych w UI
    profile.industry = ui->industryLineEdit->text();
    profile.employeeCount = ui->employeeSpinBox->value();
    profile.locationsCount = ui->locationsSpinBox->value();

    // Przetwarzanie listy zespołów (rozdzielanie po przecinku i usuwanie spacji)
    QString teamsText = ui->teamsLineEdit->text();
    profile.teams = teamsText.split(',', Qt::SkipEmptyParts);
    for(QString &team : profile.teams) {
        team = team.trimmed();
    }

    // Pobieranie wartości z list rozwijanych i pól wyboru
    profile.priority = ui->priorityComboBox->currentText();
    profile.budget = ui->budgetComboBox->currentText();
    profile.hasServerRoom = ui->serverRoomCheckBox->isChecked();

    // Pobieranie notatek (używamy toPlainText(), ponieważ to zwykle QPlainTextEdit)
    profile.additionalNotes = ui->additionalNotesEdit->toPlainText();

    return profile;
}