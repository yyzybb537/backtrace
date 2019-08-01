#include <stdio.h>
#include "backtrace.h"

namespace backtrace {
    static const int kBufferLen = 64 * 1024;

    char* getBacktrace() {
        static thread_local char buf[kBufferLen];
        return buf;
    }

    int getBufferLength() {
        return kBufferLen;
    }

    extern void onExceptionConstruct();
}

namespace std {
    class exception {
        exception();
    };

    exception::exception() {
        backtrace::onExceptionConstruct();
    }
}
