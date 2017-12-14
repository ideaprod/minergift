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
    virtual void setCpuUsage() = 0;
    virtual void setCpuPriority() = 0;
    virtual void setCpuAffinity() = 0;
    virtual void setServer() = 0;
    virtual void setUserName() = 0;
    virtual void setCpuThreadNumber() = 0;

    virtual MinerStatus getStatus() = 0;
    virtual QString getHostInfo() = 0;
    virtual QString getHashRate() = 0;

signals:

public slots:
};

#endif // CORE_H
