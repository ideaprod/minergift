#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_buttonStartStop_pressed();

private:
    Ui::MainWindow *ui;
    bool started;
    void start();
    void stop();
};

#endif // MAINWINDOW_H
