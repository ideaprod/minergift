#include "CpuLimitationThread.h"

CpuLimitationThread::CpuLimitationThread(int pid, int cpu)
    : xmrigPid(pid), maxCpu(cpu)
{

}

int CpuLimitationThread::getNbCores()
{
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);
    int nbCores = sysinfo.dwNumberOfProcessors;

    return nbCores;
}

void CpuLimitationThread::run()
{
    //WIP
    CPULimiter limiter = this->maxCpu;
    int nbCores = getNbCores();

    forever {
        //limit cpu usage here.

        limiter.CalculateAndSleep(this->xmrigPid, nbCores);
        if ( QThread::currentThread()->isInterruptionRequested() )
        {
            return;
        }
    }

    qDebug()<<"From worker thread: "<<currentThreadId();
}

