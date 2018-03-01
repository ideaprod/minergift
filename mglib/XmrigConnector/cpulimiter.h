/*
 * THE WORK IS PROVIDED UNDER THE TERMS OF THIS CODE PROJECT OPEN LICENSE ("LICENSE").
 * THE WORK IS PROTECTED BY COPYRIGHT AND/OR OTHER APPLICABLE LAW.
 * ANY USE OF THE WORK OTHER THAN AS AUTHORIZED UNDER THIS LICENSE OR COPYRIGHT LAW IS PROHIBITED.
 *
 * BY EXERCISING ANY RIGHTS TO THE WORK PROVIDED HEREIN, YOU ACCEPT AND AGREE TO BE BOUND BY THE TERMS OF THIS LICENSE.
 * THE AUTHOR GRANTS YOU THE RIGHTS CONTAINED HEREIN IN CONSIDERATION OF YOUR ACCEPTANCE OF SUCH TERMS AND CONDITIONS.
 * IF YOU DO NOT AGREE TO ACCEPT AND BE BOUND BY THE TERMS OF THIS LICENSE, YOU CANNOT MAKE ANY USE OF THE WORK.
 *
 * 27th August, 2008 : This code was initialy posted by https://www.codeproject.com/Members/Lone-Developer
 * 1st March, 2018 : This code was modified for the projet MinerGift to adapt it to a process depending on the number of cores.
 *
*/
#ifndef CPULIMITER_H
#define CPULIMITER_H

#include <QtGlobal>

#ifdef Q_OS_WIN

#include <windef.h>
#include <winbase.h>

const int DEFAULT_MAX_PERCENTAGE = 20;

/*
CPULimiter:
This class helps to limit the CPU usage/consumption by a thread involving
some kind of repetitive/polling kind of operation in a loop.
The limit can be set by a user through a function of this class.
*/

class CPULimiter
{
    //This integer stores last total system time.
    //total system time is sum of time spent by system
    //in kernel, user and idle mode
    LARGE_INTEGER m_lastTotalSystemTime;

    //This integer stores last total time spent by this
    //thread in    kernel space and user space
    LARGE_INTEGER m_lastThreadUsageTime;

    //Variable used to store maximum thread CPU percentage
    //relative to system total time.
    int m_ratio;
public:

    //Constructors
    CPULimiter();
    //Constructor with maximum thread cpu usage percentage
    CPULimiter(int p_ratio);

    //****************Main function.******************
    //It evaluates CPU consumption by this thread since
    //last call to this function, until now.
    //Internally, it calculates if the thread has exceeded
    //the maximum CPU usage percentage specified.
    //if yes, it makes the thread sleep for a calculated
    //time period, to average the total usage to the limit specified.
    //Returns TRUE Successful, else FALSE

    BOOL CalculateAndSleep(DWORD processId, int nbCores);

    //Inline setter function
    inline void SetRatio(int p_ratio){m_ratio = p_ratio;}
};
#endif // CPULIMITER_H
#endif // Q_OS_WIN
