#ifndef COMPANYINPUTDIALOG_H
#define COMPANYINPUTDIALOG_H

#include <QDialog>
#include "../core/CompanyProfile.h"

// Przestrzeń nazw generowana automatycznie przez Qt Designer
QT_BEGIN_NAMESPACE
namespace Ui { class CompanyInputDialog; }
QT_END_NAMESPACE

/**
 * @brief Klasa CompanyInputDialog odpowiada za interfejs formularza danych firmy.
 * Umożliwia zebranie szczegółowych informacji o infrastrukturze i potrzebach klienta.
 */
class CompanyInputDialog : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Konstruktor okna dialogowego.
     * @param parent Wskaźnik na obiekt nadrzędny (zazwyczaj MainWindow).
     */
    explicit CompanyInputDialog(QWidget *parent = nullptr);

    /**
     * @brief Destruktor klasy.
     */
    ~CompanyInputDialog();

    /**
     * @brief Metoda zwracająca dane wprowadzone przez użytkownika w formie struktury.
     * @return Obiekt CompanyProfile zawierający stan wszystkich pól formularza.
     */
    CompanyProfile getProfile() const;

private:
    Ui::CompanyInputDialog *ui; // Wskaźnik na wygenerowaną klasę interfejsu (z pliku .ui)
};

#endif // COMPANYINPUTDIALOG_H