#include <QDebug>

#include "XmrigConnector.h"

XmrigConnector::XmrigConnector(QObject *parent)
  : MinerApi(parent)
{
    qDebug() << "XmrigConnector construct";
}

int XmrigConnector::start()
{
    qDebug() << "XmrigConnector start";
    return 1;
}

int XmrigConnector::stop()
{
    qDebug() << "XmrigConnector stop";
    return 1;
}

int XmrigConnector::getCpuUsage()
{
    return 1;
}

void XmrigConnector::setCpuUsage(int cpuUsage)
{
    Q_UNUSED(cpuUsage);
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
    return "userName";
}

void XmrigConnector::setUserName(QString userName)
{
    Q_UNUSED(userName);
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
