#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CompanyInputDialog.h"
#include "../llm/PromptBuilder.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_generateButton_clicked()
{
    // 1. Tworzymy dialog
    CompanyInputDialog dialog(this);

    // 2. Jeśli użytkownik kliknie OK (Accepted)
    if (dialog.exec() == QDialog::Accepted) {

        // 3. Pobieramy profil z formularza
        CompanyProfile profile = dialog.getProfile();

        // 4. Budujemy prompt przez statyczną metodę klasy PromptBuilder
        QString prompt = PromptBuilder::buildNetworkPrompt(profile);

        // 5. Wstawiamy tekst do pola w oknie głównym
        // Upewnij się, że w Designerze nazwałeś to pole: promptDisplay
        if (ui->promptDisplay) {
            ui->promptDisplay->setPlainText(prompt);
        } else {
            qDebug() << "BŁĄD: Nie znaleziono obiektu promptDisplay!";
        }
    }
}