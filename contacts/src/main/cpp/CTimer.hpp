//
// Created by Z003XHTA on 7/22/2018.
//
#include "CTimer.h"
#include "TimerException.h"
//#include "../../../../../../../../../../../opt/android/android-sdk-linux/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/c++/v1/ctime"
//#include "../../../../../../../../../../../opt/android/android-sdk-linux/ndk-bundle/toolchains/llvm/prebuilt/linux-x86_64/sysroot/usr/include/time.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <errno.h>

namespace contacts {
template <class T>
const unsigned long CTimer<T>::MILLISECONDS_TO_NANOSECONDS_FACTOR = 1000000;
template <class T>
void CTimer<T>::TimerThreadFunc(union sigval arg)
{
    CTimer<T>* pThis = static_cast<CTimer<T>*>(arg.sival_ptr);
    pThis->GetHandler()->OnTimeOut();
}

template <class T>
CTimer<T>::CTimer(T * pHandler):m_Handler(pHandler),
                                m_TimerType(TimerType::MULTI_SHOT),
                                m_nInterval(10),
                                m_TimerID(NULL)
{

}
template <class T>
T*  CTimer<T>::GetHandler()    { return m_Handler; }

template <class T>
TimerType  CTimer<T>::GetTimerType()
{
    return m_TimerType;
}
template <class T>
void  CTimer<T>::SetTimerType(TimerType type)
{
    m_TimerType = type;
}
template <class T>
void  CTimer<T>::SetInterval(long sec)
{
    m_nInterval = sec;
}
template <class T>
int  CTimer<T>::GetInterval()
{
    return m_nInterval;
}

template <class T>
void CTimer<T>::Start(long sec)
{
    StopTimer();
    StartTimer(sec);
    m_Handler->OnStart();
}

template <class T>
void CTimer<T>::Start()
{
    StopTimer();
    StartTimer(m_nInterval);
    m_Handler->OnStart();
}

template <class T>
void CTimer<T>::StopTimer() {
    if(m_TimerID != NULL)
    {
        try {
            Stop();
        } catch(contacts::CTimerException& ex)
        {
        }
    }
}


template <class T>
void CTimer<T>::Stop()
{
    int status = timer_delete(m_TimerID);
    if (status == -1){
        HandleTimerDeleteError();
        return;
    }
    m_TimerID = NULL;
    m_Handler->OnStop();
}

template <class T>
void CTimer<T>::HandleTimerCreateError() const {

}

template <class T>
void CTimer<T>::HandleTimerSetTimeError() const {

}

template <class T>
void CTimer<T>::HandleTimerDeleteError() const {

}

template <class T>
void CTimer<T>::StartTimer(long sec) {

    int status;
    struct itimerspec ts;
    struct sigevent se;

    /*
     * Set the sigevent structure to cause the signal to be
     * delivered by creating a new thread.
     */
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_value.sival_ptr = this;
    se.sigev_notify_function = TimerThreadFunc;
    se.sigev_notify_attributes = NULL;

    ts.it_value.tv_sec = sec;
    ts.it_value.tv_nsec = 0;
    ts.it_interval.tv_sec = sec;
    ts.it_interval.tv_nsec = 0;


    status = timer_create(CLOCK_REALTIME, &se, &m_TimerID);
    if (status == -1) {
        HandleTimerCreateError();
        return;
    }

    status = timer_settime(m_TimerID, 0, &ts, 0);
    if (status == -1) {
        HandleTimerSetTimeError();
        return;
    }

}
}