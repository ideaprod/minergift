#include "XmrigConnector.h"

XmrigConnector::XmrigConnector(QObject *parent)
  : MinerApi(parent)
{
    qDebug() << "XmrigConnector construct";
}

int XmrigConnector::start()
{
    qDebug() << "XmrigConnector start";
    QString program = "./xmrig";
    QStringList arguments;
    arguments << "-o" << "stratum+tcp://xmr.pool.minergate.com:45560" << "-u" << this->getUserName() << "-k";
    qDebug() << "args: " << arguments;

    myProcess = new QProcess();
    myProcess->start(program, arguments);
    return 1;
}

int XmrigConnector::stop()
{
    qDebug() << "XmrigConnector stop";
    myProcess->kill();
    return 1;
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
    return MinerStatus::STOPPED;
}

QString XmrigConnector::getHostInfo()
{
    return "hostInfo";
}

QString XmrigConnector::getHashRate()
{
    return "hashRate";
}
