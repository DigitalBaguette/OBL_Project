#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// Forward declarations - upraszczają kompilację
class OllamaClient;
namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleAIResponse(const QString& response);
    void handleAIError(const QString& error);

private:
    Ui::MainWindow *ui;
    OllamaClient *ollama;
};

#endif