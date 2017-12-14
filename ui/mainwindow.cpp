#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    conf = new Conf();
    ui->setupUi(this);

    //ToDo : dynamically load connectors instead of instanciate them
    this->xmc = new XmrigConnector();
    this->start();

    qDebug() << "description: " << conf->value("description");
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::start()
{
    qDebug() << "Starting...";
    this->xmc->start();
    started = true;
}

void MainWindow::stop()
{
    qDebug() << "Stoping...";
    this->xmc->stop();
    started = false;
}
