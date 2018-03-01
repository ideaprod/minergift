#ifndef CPULIMITATIONTHREAD_H
#define CPULIMITATIONTHREAD_H

#include <QtGlobal>

#ifdef Q_OS_WIN

#include <QtCore>
#include "CpuLimiter.h"



class CpuLimitationThread : public QThread
{
public:
    CpuLimitationThread(int xmrigPid, int maxCpu);

private:
    void run();
    int xmrigPid;
    int maxCpu;
    int getNbCores();
};

#endif // Q_OS_WIN

#endif // CPULIMITATIONTHREAD_H
