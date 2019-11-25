
//#include<iostream>
#include "CtimerTest.h"
#include "CTimer.h"
#include "contacts.h"

#include <android/log.h>
#define  LOG_TAG    "contacs-sdk"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace contacts {

void contacts::CTimerTest::OnStart()
{
    LOGD("Timer started");
}
void contacts::CTimerTest::OnStop()
{
    LOGD("Timer stop");
}
void contacts::CTimerTest::OnTimeOut()
{
    LOGD("Timer event Triggered");
    contacts::Contacts callerCtx;
    callerCtx.getCtx()->updateContacts();

}

void contacts::CTimerTest::Test()
{
    //static contacts::Contacts callerCtx;
    //contacts::Contacts ctx = ctx.getCtx();
    //contacts::CTimerTest::callerCtx = ctx;


    CTimer<CTimerTest> timer(this);
    timer.SetInterval(30);//seconds
    try {
        LOGD("Timer start request");
        timer.Start();
    } catch(CTimerException& ex)
    {
        LOGD("Timer exception:");
    }
}

}