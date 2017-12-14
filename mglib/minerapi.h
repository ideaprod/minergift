#ifndef CORE_H
#define CORE_H

#include <QObject>
#include <QString>

class MinerApi : public QObject
{
    Q_OBJECT
public:
    enum MinerStatus {
      STARTED,
      STOPPED
    };
    Q_ENUM(MinerStatus)

    explicit MinerApi(QObject *parent = 0) { Q_UNUSED(parent) }
    virtual ~MinerApi() {}
    virtual int start() = 0;
    virtual int stop() = 0;
    virtual int getCpuUsage() = 0;
    virtual void setCpuUsage(int cpuUsage) = 0;
    virtual int getCpuPriority() = 0;
    virtual void setCpuPriority(int cpuPriority) = 0;
    virtual int getCpuAffinity() = 0;
    virtual void setCpuAffinity(int cpuAffinity) = 0;
    virtual int getCpuThreadNumber() = 0;
    virtual void setCpuThreadNumber(int cpuThreadNumber) = 0;
    virtual QString getServer() = 0;
    virtual void setServer(QString server) = 0;
    virtual QString getUserName() = 0;
    virtual void setUserName(QString userName) = 0;

    virtual MinerStatus getStatus() = 0;
    virtual QString getHostInfo() = 0;
    virtual QString getHashRate() = 0;

signals:

public slots:
};

#endif // CORE_H
