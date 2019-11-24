
//#include<iostream>
#include "CtimerTest.h"
#include "CTimer.h"

#include <android/log.h>
#define  LOG_TAG    "contacs-sdk"

#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

namespace contacts {

void contacts::CTimerTest::OnStart()
{
    LOGD("Timer started");
    //std::cout<<"Timer started";
}
void contacts::CTimerTest::OnStop()
{
    LOGD("Timer stop");
    //std::cout<<"Timer Stopped";
}
void contacts::CTimerTest::OnTimeOut()
{
    LOGD("Timer event Triggered");

}

void contacts::CTimerTest::Test()
{
    CTimer<CTimerTest> timer(this);
    timer.SetTimerType(TimerType::MULTI_SHOT);
    timer.SetInterval(30000);
    try {
      //  std::cout<<"Timer start";
        LOGD("Timer start request");
        timer.Start();
    } catch(CTimerException& ex)
    {
        //std::cout<<"Timer exception:"<<ex.what();
    }

   // sleep(60);
}
}