#ifndef XMRIGCONNECTOR_H
#define XMRIGCONNECTOR_H

#include "minerapi.h"

class XmrigConnector : public MinerApi
{
public:
    XmrigConnector(QObject *parent = 0);

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
};

#endif // XMRIGCONNECTOR_H
