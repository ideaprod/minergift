#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QComboBox>

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

protected:
    void onSliderChange();

private slots:
    void on_buttonStartStop_pressed();
    void on_sliderRate_valueChanged();
    void on_sliderRate_sliderMoved();

    void iconActivated(QSystemTrayIcon::ActivationReason reason);

private:
    Ui::MainWindow *ui;
    XmrigConnector * xmc;
    Conf * conf;

    bool started;
    void start();
    void stop();

    void initConnectors();
    void initConf();
    void initUi();
    void initIcons();

    QIcon * playIcon;
    QIcon * stopIcon;
    QIcon * trayIcon;
    QSystemTrayIcon * systemTrayIcon;
    QMenu *trayIconMenu;
    void createActions();
    void createTrayIcon();
    void initSysTray();
    void changeEvent(QEvent *event);

    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    void hideSlider();
};

#endif // MAINWINDOW_H
