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
    stopIcon = new QIcon();
    stopIcon->addFile("://images/red-stop-button-plain-icon-th.png");
    playIcon = new QIcon();
    playIcon->addFile("://images/green-plain-play-button-icon-th.png");
}

void MainWindow::initUi()
{
    ui->setupUi(this);
    initIcons();
    ui->lcdRate->hide();
    ui->sliderRate->hide();
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
    qDebug() << "Slider moved";
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
