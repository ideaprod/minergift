#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    initConf();
    initUi();
    initConnectors();
    this->start();
}

MainWindow::~MainWindow()
{
    //ToDo : dynamically destroy connectors instead of calling destructor
    this->xmc->~XmrigConnector();
    delete ui;
}

void MainWindow::initConf()
{
    this->conf = new Conf("./miner.json");
}

void MainWindow::initIcons()
{
    stopIcon = new QIcon("://images/red-stop-button-plain-icon-th.png");
    playIcon = new QIcon("://images/green-plain-play-button-icon-th.png");
    trayIcon = new QIcon("://images/gavel-297564_960_720.png");
}

void MainWindow::initSysTray()
{
    createActions();
    createTrayIcon();
    connect(systemTrayIcon, &QSystemTrayIcon::activated, this, &MainWindow::iconActivated);
    systemTrayIcon->show();
}

void MainWindow::hideSlider()
{
    ui->lcdRate->hide();
    ui->sliderRate->hide();
}

void MainWindow::initUi()
{
    ui->setupUi(this);
    initIcons();
    initSysTray();
    hideSlider();
}

void MainWindow::initConnectors()
{
    //ToDo : dynamically load connectors instead of instanciate them
    this->xmc = new XmrigConnector();
    this->xmc->setUserName(conf->value("username"));
}

void MainWindow::on_buttonStartStop_pressed()
{
    qDebug() << "Button pressed";
    if (started)
    {
        this->stop();
    }
    else
    {
        this->start();
    }
}

void MainWindow::onSliderChange()
{
    this->xmc->setCpuUsage(ui->sliderRate->value());
}

void MainWindow::on_sliderRate_valueChanged()
{
    qDebug() << "Slider value changed:" << ui->sliderRate->value();
    onSliderChange();
}

void MainWindow::on_sliderRate_sliderMoved()
{
    onSliderChange();
}

void MainWindow::start()
{
    qDebug() << "Starting...";
    this->xmc->start();
    ui->sliderRate->setEnabled(false);
    ui->buttonStartStop->setText("Stop");
    ui->buttonStartStop->setIcon(*stopIcon);
    started = true;
}

void MainWindow::stop()
{
    qDebug() << "Stopping...";
    this->xmc->stop();
    ui->sliderRate->setEnabled(true);
    ui->buttonStartStop->setText("Start");
    ui->buttonStartStop->setIcon(*playIcon);
    started = false;
}

void MainWindow::createActions()
{
    minimizeAction = new QAction(tr("Mi&nimize"), this);
    minimizeAction->setIcon(QIcon("://images/if_16-Input_2123951.png"));
    connect(minimizeAction, &QAction::triggered, this, &QMainWindow::hide);

    restoreAction = new QAction(tr("&Restore"), this);
    restoreAction->setIcon(QIcon("://images/if_15-Output_2123957.png"));
    connect(restoreAction, &QAction::triggered, this, &QMainWindow::showNormal);

    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setIcon(QIcon("://images/if_9-Cancel_2123880.png"));
    connect(quitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
}

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    systemTrayIcon = new QSystemTrayIcon(this);
    systemTrayIcon->setContextMenu(trayIconMenu);
    systemTrayIcon->setIcon(*trayIcon);
}

void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
            restoreAction->trigger();
            break;
        default:
            ;
    }
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    if(event->type() == QEvent::WindowStateChange)
    {
        if(isMinimized())
        {
            this->hide();
        }
        else
        {
            this->show();
        }

        if(!this->isVisible())
        {
            this->show();
        }
        else
        {
            this->hide();
        }
    }
}
