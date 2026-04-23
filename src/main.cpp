/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji OBL_Project.
 */
#include <QApplication>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Dane aplikacji - ważne dla systemowego zapisu plików (wymóg nr 6 i 8)
    QApplication::setApplicationName("NetworkAI_Analyzer");
    QApplication::setOrganizationName("JPO_Project");
    QApplication::setApplicationVersion("1.0.0");

    MainWindow w;
    w.show();

    return a.exec();
}