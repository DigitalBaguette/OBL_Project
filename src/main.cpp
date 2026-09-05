/**
 * @file main.cpp
 * @brief Punkt wejścia aplikacji OBL_Project.
 */
#include <QApplication>
#include "gui/MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    QApplication::setApplicationName("NetworkAI_Analyzer");
    QApplication::setOrganizationName("JPO_Project");
    QApplication::setApplicationVersion("1.0.0");

    MainWindow w;
    w.show();

    return a.exec();
}
