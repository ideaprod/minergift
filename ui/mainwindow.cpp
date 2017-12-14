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
    delete ui;
}

void MainWindow::initConf()
{
    this->conf = new Conf("./miner.json");
}

void MainWindow::initUi()
{
    ui->setupUi(this);
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
    started = true;
}

void MainWindow::stop()
{
    qDebug() << "Stoping...";
    this->xmc->stop();
    ui->sliderRate->setEnabled(true);
    started = false;
}
