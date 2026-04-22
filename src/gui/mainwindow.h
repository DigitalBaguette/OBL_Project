#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../core/CompanyProfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Ta nazwa MUSI odpowiadać schematowi: on_NAZWAOBIEKTU_clicked
    void on_generateButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H