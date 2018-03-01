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
 *   1st March, 2018 : This code was modified for the projet MinerGift to adapt it to a process depending
 * on the number of cores.
 *
*/

#include "CpuLimiter.h"
#include <iostream>

#include <psapi.h>

//constructors
CPULimiter::CPULimiter(int p_ratio)
:m_ratio(p_ratio)
{
    ::ZeroMemory( &m_lastTotalSystemTime, sizeof(LARGE_INTEGER));
    ::ZeroMemory( &m_lastThreadUsageTime, sizeof(LARGE_INTEGER));
}

CPULimiter::CPULimiter()
{
    ::ZeroMemory( &m_lastTotalSystemTime, sizeof(LARGE_INTEGER));
    ::ZeroMemory( &m_lastThreadUsageTime, sizeof(LARGE_INTEGER));
    m_ratio = DEFAULT_MAX_PERCENTAGE;
}

BOOL CPULimiter::CalculateAndSleep(DWORD processId, int nbCores)
{
    //Declare variables;
    FILETIME sysIdle, kerUsage, userUsage, processKern
                   , processUser, processCreat, processExit;
    LARGE_INTEGER tmpVar, thisSysTime, thisProcessTime;

    //Get system kernel, user and idle times
    if(!::GetSystemTimes(&sysIdle, &kerUsage, &userUsage))
    {
        return FALSE;
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);

    //Get Process user and kernel times
    if(!::GetProcessTimes(processHandle, &processCreat, &processExit, &processKern, &processUser))
    {
        return FALSE;
    }

    //Calculates total system times
    //This is sum of time used by system in kernel, user and idle mode.

    tmpVar.LowPart = sysIdle.dwLowDateTime;
    tmpVar.HighPart = sysIdle.dwHighDateTime;
    thisSysTime.QuadPart = tmpVar.QuadPart;

    tmpVar.LowPart = kerUsage.dwLowDateTime;
    tmpVar.HighPart = kerUsage.dwHighDateTime;
    thisSysTime.QuadPart = thisSysTime.QuadPart + tmpVar.QuadPart;

    tmpVar.LowPart = userUsage.dwLowDateTime;
    tmpVar.HighPart = userUsage.dwHighDateTime;
    thisSysTime.QuadPart = thisSysTime.QuadPart + tmpVar.QuadPart;

    //Calculates time spent by this thread in user and kernel mode.

    tmpVar.LowPart = processKern.dwLowDateTime;
    tmpVar.HighPart = processKern.dwHighDateTime;
    thisProcessTime.QuadPart = tmpVar.QuadPart;

    tmpVar.LowPart = processUser.dwLowDateTime;
    tmpVar.HighPart = processUser.dwHighDateTime;
    thisProcessTime.QuadPart = thisProcessTime.QuadPart + tmpVar.QuadPart;

    //Check if this is first time this function is called
    //if yes, escape rest after copying current system and thread time
    //for further use
    //Also check if the ratio of differences between current and previous times
    //exceeds the specified ratio.
    if( thisProcessTime.QuadPart != 0
        && (((thisProcessTime.QuadPart - m_lastThreadUsageTime.QuadPart)*100)
          - ((thisSysTime.QuadPart - m_lastTotalSystemTime.QuadPart)*m_ratio)) > 0)
    {
        //Calculate the time interval to sleep for averaging the extra CPU usage
        //by this thread.

        LARGE_INTEGER timetosleepin100ns;
        timetosleepin100ns.QuadPart =
                          (((thisProcessTime.QuadPart - m_lastThreadUsageTime.QuadPart)*100)/m_ratio)
                        - (thisSysTime.QuadPart - m_lastTotalSystemTime.QuadPart);

        //check if time is less than a millisecond, if yes, keep it for next time.
        if((timetosleepin100ns.QuadPart/10000) <= 0)
        {
            return FALSE;
        }

        //Time to Sleep :)
        DebugActiveProcess(processId);
        Sleep((timetosleepin100ns.QuadPart/10000)/nbCores);
        DebugActiveProcessStop(processId);
    }

    CloseHandle(processHandle);

    //Copy usage time values for next time calculations.
    m_lastTotalSystemTime.QuadPart = thisSysTime.QuadPart;
    m_lastThreadUsageTime.QuadPart = thisProcessTime.QuadPart;
    return TRUE;
}
