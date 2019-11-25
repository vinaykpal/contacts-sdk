//
// Timer handler class
//

#ifndef MYAPPLICATION_CTIMERTEST_H
#define MYAPPLICATION_CTIMERTEST_H

#include "contacts.h"

namespace contacts {
    class CTimerTest {
    public:
        void OnStart();

        void OnStop();

        void OnTimeOut();

        void Test();



    };
}
#endif //MYAPPLICATION_CTIMERTEST_H
