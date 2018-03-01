#ifndef XMRIGCONNECTOR_H
#define XMRIGCONNECTOR_H

#include <QDebug>
#include <QProcess>

#include "minerapi.h"
#include "CpuLimitationThread.h"

class XmrigConnector : public MinerApi
{

Q_OBJECT

public:
    XmrigConnector(MinerApi *parent = 0);
    ~XmrigConnector();

    int start();
    int stop();
    int getCpuUsage();
    void setCpuUsage(int cpuUsage);
    int getCpuPriority();
    void setCpuPriority(int cpuPriority);
    int getCpuAffinity();
    void setCpuAffinity(int cpuAffinity);
    int getCpuThreadNumber();
    void setCpuThreadNumber(int cpuThreadNumber);
    QString getServer();
    void setServer(QString server);
    QString getUserName();
    void setUserName(QString userName);

    MinerStatus getStatus();
    QString getHostInfo();
    QString getHashRate();    

private:
    QString userName;
    int cpuUsage;

    QProcess *xmrigProcess;
    bool xmrigProcessStarted;
    int xmrigPid;

    QProcess *cpulimitProcess;
    CpuLimitationThread *cpuLimitationThread;

    void startXmrig();

    void startCpulimit();

    void stopCpuLimit();

private slots:

    void displayStandardOutput();
    void displayErrorOutput();
};

#endif // XMRIGCONNECTOR_H
