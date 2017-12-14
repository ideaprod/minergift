#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "constants.h"
#include "minerapi.h"
#include "XmrigConnector/XmrigConnector.h"
#include "conf.h"

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
    XmrigConnector *xmc;
    Conf *conf;
    void initConnectors();
    void initConf();
    void initUi();
};

#endif // MAINWINDOW_H
