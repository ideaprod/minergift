#include "XmrigConnector.h"

XmrigConnector::XmrigConnector(MinerApi *parent)
  : MinerApi(parent),
    xmrigProcessStarted(false)
{
    qDebug() << "XmrigConnector construct";
    this->setCpuUsage(10);
}

int XmrigConnector::start()
{
    qDebug() << "XmrigConnector start";
    if (!xmrigProcessStarted) {
        startXmrig();
        startCpulimit();
        return 1;
    }
    else {
        qDebug() << "XmrigConnector start failed, already started";
        return 0;
    }
}

void XmrigConnector::startXmrig()
{
    QString xmrigProgram = "./xmrig";
    QStringList xmrigArguments;
    xmrigArguments << "-o" << "stratum+tcp://xmr.pool.minergate.com:45560" << "-u" << this->getUserName() << "-k"
              << "--no-color"
              << "--threads=1"
              << "--av=0"
              //<< "--max-cpu-usage=" + QString::number(this->getCpuUsage())
              << "--cpu-priority" << "1";
    qDebug() << "args: " << xmrigArguments;

    xmrigProcess = new QProcess();
    xmrigProcess->setReadChannelMode(QProcess::MergedChannels);
    xmrigProcess->start(xmrigProgram, xmrigArguments);

    QObject::connect(xmrigProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(displayProcessOutput()));
    xmrigPid = xmrigProcess->pid();

    xmrigProcessStarted = true;
}

void XmrigConnector::startCpulimit()
{
    QString cpulimitProgram = "./cpulimit";
    QStringList cpulimitArguments;
    cpulimitArguments << "-l" + QString::number(this->getCpuUsage())
              << "-p" + QString::number(xmrigPid);
    qDebug() << "args: " << cpulimitArguments;

    cpulimitProcess = new QProcess();
    cpulimitProcess->setReadChannelMode(QProcess::MergedChannels);
    cpulimitProcess->start(cpulimitProgram, cpulimitArguments);

    QObject::connect(cpulimitProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(displayProcessOutput()));
}

int XmrigConnector::stop()
{
    qDebug() << "XmrigConnector stop";

    if (xmrigProcessStarted) {
        xmrigProcess->terminate();
        xmrigProcessStarted = false;
    }
    return 1;
}

void XmrigConnector::displayProcessOutput()
{
    qDebug() << xmrigProcess->readAllStandardOutput();
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
    if (xmrigProcessStarted) {
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
