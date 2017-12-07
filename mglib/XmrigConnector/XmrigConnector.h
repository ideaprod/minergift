#ifndef XMRIGCONNECTOR_H
#define XMRIGCONNECTOR_H

#include "minerapi.h"

class XmrigConnector : public MinerApi
{
public:
    XmrigConnector(QObject *parent = 0) : MinerApi(parent)
    {
        qDebug() << "XmrigConnector construct";
    }

    int start();
    int stop();
    void setCpuUsage();
    void setCpuPriority();
    void setCpuAffinity();
    void setServer();
    void setUserName();
    void setCpuThreadNumber();

    QString getStatus();
    QString getHostInfo();
    QString getHashRate();    

};

#endif // XMRIGCONNECTOR_H
