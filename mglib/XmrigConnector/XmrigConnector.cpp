#include "XmrigConnector.h"

XmrigConnector::XmrigConnector(MinerApi *parent)
  : MinerApi(parent),
    processStarted(false)
{
    qDebug() << "XmrigConnector construct";
    this->setCpuUsage(10);
}

int XmrigConnector::start()
{
    qDebug() << "XmrigConnector start";
    if (!processStarted) {
        QString program = "./xmrig";
        QStringList arguments;
        arguments << "-o" << "stratum+tcp://xmr.pool.minergate.com:45560" << "-u" << this->getUserName() << "-k"
                  << "--no-color"
                  << "--threads=1"
                  << "--av=0"
                  << "--max-cpu-usage=" + QString::number(this->getCpuUsage())
                  << "--cpu-priority" << "1";
        qDebug() << "args: " << arguments;

        myProcess = new QProcess();
        myProcess->setReadChannelMode(QProcess::MergedChannels);
        myProcess->start(program, arguments);

        QObject::connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(displayProcessOutput()));

        processStarted = true;
        return 1;
    }
    else {
        qDebug() << "XmrigConnector start failed, already started";
        return 0;
    }
}

int XmrigConnector::stop()
{
    qDebug() << "XmrigConnector stop";

    if (processStarted) {
        myProcess->terminate();
        processStarted = false;
    }
    return 1;
}

void XmrigConnector::displayProcessOutput()
{
    qDebug() << myProcess->readAllStandardOutput();
}

int XmrigConnector::getCpuUsage()
{
    return this->cpuUsage;
}

void XmrigConnector::setCpuUsage(int cpuUsage)
{
    this->cpuUsage = cpuUsage;
}

int XmrigConnector::getCpuPriority()
{
    return 1;
}

void XmrigConnector::setCpuPriority(int cpuPriority)
{
    Q_UNUSED(cpuPriority);
}

int XmrigConnector::getCpuAffinity()
{
    return 1;
}

void XmrigConnector::setCpuAffinity(int cpuAffinity)
{
    Q_UNUSED(cpuAffinity);
}

int XmrigConnector::getCpuThreadNumber()
{
    return 1;
}

void XmrigConnector::setCpuThreadNumber(int cpuThreadNumber)
{
    Q_UNUSED(cpuThreadNumber);
}

QString XmrigConnector::getServer()
{
    return "server";
}

void XmrigConnector::setServer(QString server)
{
    Q_UNUSED(server);
}

QString XmrigConnector::getUserName()
{
    return this->userName;
}

void XmrigConnector::setUserName(QString userName)
{
    this->userName = userName;
}

MinerApi::MinerStatus XmrigConnector::getStatus()
{
    if (processStarted) {
        return MinerStatus::STARTED;
    }
    else {
        return MinerStatus::STOPPED;
    }
}

QString XmrigConnector::getHostInfo()
{
    return "hostInfo";
}

QString XmrigConnector::getHashRate()
{
    return "hashRate";
}
