#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->start();
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
    started = true;
}

void MainWindow::stop()
{
    qDebug() << "Stoping...";
    started = false;
}
