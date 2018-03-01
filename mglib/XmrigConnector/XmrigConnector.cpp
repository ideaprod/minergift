
#include "XmrigConnector.h"


XmrigConnector::XmrigConnector(MinerApi *parent)
  : MinerApi(parent),
    xmrigProcessStarted(false)
{
    qDebug() << "XmrigConnector construct";
    this->setCpuUsage(10);
}

XmrigConnector::~XmrigConnector()
{
    if (xmrigProcessStarted) {
        this->stop();
    }
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
              //<< "--threads=1"
              //<< "--av=0"
              //<< "--max-cpu-usage=" + QString::number(this->getCpuUsage())
              << "--max-cpu-usage=100"
              //<< "--cpu-affinity" << "0"
              << "--cpu-priority" << "1";
    qDebug() << "args: " << xmrigArguments;

    xmrigProcess = new QProcess();
    xmrigProcess->setReadChannelMode(QProcess::MergedChannels);
    xmrigProcess->start(xmrigProgram, xmrigArguments);

    QObject::connect(xmrigProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(displayStandardOutput()));
    QObject::connect(xmrigProcess, SIGNAL(readyReadStandardError()), this, SLOT(displayErrorOutput()));

    xmrigPid = xmrigProcess->processId();

    xmrigProcessStarted = true;
}

#if defined(Q_OS_LINUX)
void XmrigConnector::startCpulimit()
{
    cpulimitProcess = new QProcess();

    QString cpulimitProgram = "./cpulimit";
    QStringList cpulimitArguments;
    cpulimitArguments << "-l" + QString::number(this->getCpuUsage())
              << "-p" + QString::number(xmrigPid);
    qDebug() << "args: " << cpulimitArguments;


    cpulimitProcess->setReadChannelMode(QProcess::MergedChannels);
    cpulimitProcess->start(cpulimitProgram, cpulimitArguments);

    QObject::connect(cpulimitProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(displayStandardOutput()));
    QObject::connect(cpulimitProcess, SIGNAL(readyReadStandardError()), this, SLOT(displayErrorOutput()));
}

void XmrigConnector::stopCpuLimit()
{
    cpulimitProcess->close();
}

#elif defined(Q_OS_WIN)
void XmrigConnector::startCpulimit()
{
    cpuLimitationThread = new CpuLimitationThread(xmrigPid,this->getCpuUsage());
    cpuLimitationThread->start();
}

void XmrigConnector::stopCpuLimit()
{
    cpuLimitationThread->requestInterruption();
}
#endif

int XmrigConnector::stop()
{
    qDebug() << "XmrigConnector stop";
    if (xmrigProcessStarted) {
        qDebug() << "Closing and killing xmrig and cpulimit processes";
        xmrigProcess->close();
        stopCpuLimit();
        xmrigProcessStarted = false;
    }
    return 1;
}

void XmrigConnector::displayStandardOutput()
{
    QByteArray xmrigProcessLogs = xmrigProcess->readAllStandardOutput();
    if (! xmrigProcessLogs.isEmpty()) {
        qDebug() << "xmrigProcess" << xmrigProcessLogs;
    }
    #if defined(Q_OS_LINUX)
    QByteArray cpulimitProcessLogs = cpulimitProcess->readAllStandardOutput();
    if (! cpulimitProcessLogs.isEmpty()) {
        qDebug() << "cpulimitProcess" << cpulimitProcessLogs;
    }
    #endif
}

void XmrigConnector::displayErrorOutput()
{
    QByteArray xmrigProcessLogs = xmrigProcess->readAllStandardError();
    if (! xmrigProcessLogs.isEmpty()) {
        qCritical() << "xmrigProcess ERROR" << xmrigProcessLogs;
    }

    #if defined(Q_OS_LINUX)
    QByteArray cpulimitProcessLogs = cpulimitProcess->readAllStandardError();
    if (! cpulimitProcessLogs.isEmpty()) {
        qCritical() << "cpulimitProcess ERROR" << cpulimitProcessLogs;
    }
    #endif
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
