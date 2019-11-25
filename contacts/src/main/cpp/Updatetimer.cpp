
//#include<iostream>
#include "Updatetimer.h"
#include "CTimer.h"
#include "contacts.h"

#include <android/log.h>
#define  LOG_TAG    "contacs-sdk"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace contacts {

void contacts::Updatetimer::OnStart()
{
    LOGD("Timer started");
}
void contacts::Updatetimer::OnStop()
{
    LOGD("Timer stop");
}
void contacts::Updatetimer::OnTimeOut()
{
    LOGD("Timer event Triggered");
    contacts::Contacts callerCtx;
    callerCtx.getCtx()->updateContacts();

}

void contacts::Updatetimer::Test()
{
    CTimer<Updatetimer> timer(this);
    timer.SetInterval(30);//seconds interval
    try {
        LOGD("Timer start request");
        timer.Start();
    } catch(UpdatetimerException& ex)
    {
        LOGD("Timer exception:");
    }
}

}