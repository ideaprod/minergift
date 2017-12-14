#include <QDebug>

#include "XmrigConnector.h"

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

void XmrigConnector::setCpuUsage()
{

}

void XmrigConnector::setCpuPriority()
{

}

void XmrigConnector::setCpuAffinity()
{

}

void XmrigConnector::setServer()
{

}

void XmrigConnector::setUserName()
{

}

void XmrigConnector::setCpuThreadNumber()
{

}

MinerApi::MinerStatus XmrigConnector::getStatus()
{
    return MinerStatus::STOPPED;
}

QString XmrigConnector::getHostInfo()
{
    return "";
}

QString XmrigConnector::getHashRate()
{
    return "";
}
