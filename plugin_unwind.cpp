#define UNW_LOCAL_ONLY
#include "libunwind.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <cxxabi.h>
#include <string.h>

namespace backtrace
{

extern char* getBacktrace();
extern int getBufferLength();

static double g_ratio = 1;

void setRatio(double ratio)
{
    g_ratio = ratio;
}

void onExceptionConstruct()
{
    static double ratio = 1;
    ratio += g_ratio;
    if (ratio < 1)
        return ;
    ratio -= 1;

    unw_cursor_t cursor;
    unw_context_t uc;
    unw_word_t ip, sp;
    char buf[8 * 1024];
    unw_word_t offset;
    unw_getcontext(&uc);            // store registers
    unw_init_local(&cursor, &uc);   // initialze with context

    int pos = 0;
    while (unw_step(&cursor) > 0) {                         // unwind to older stack frame
        unw_get_reg(&cursor, UNW_REG_IP, &ip);              // read register, rip
        unw_get_reg(&cursor, UNW_REG_SP, &sp);              // read register, rbp
        unw_get_proc_name(&cursor, buf, sizeof(buf) - 1, &offset);     // get name and offset

        char spbuf[8 * 1024] = {};
        int len = 0;
        int status;
        char* demangled = abi::__cxa_demangle(buf, 0, 0, &status);
        if (status == 0) {
            len = snprintf(spbuf, sizeof(spbuf), "0x%016lx <%s+0x%lx>\n", ip, demangled, offset);   // x86_64, unw_word_t == uint64_t
            free(demangled);
        } else {
            len = snprintf(spbuf, sizeof(spbuf), "0x%016lx <%s+0x%lx>\n", ip, buf, offset);   // x86_64, unw_word_t == uint64_t
        }

        if (len > 0 && len <= (int)sizeof(spbuf)) {
            if (pos + len < getBufferLength()) {
                memcpy(getBacktrace() + pos, spbuf, len);
                pos += len;
                *(getBacktrace() + pos) = '\0';
            } else {
                break;
            }
        }
    }
}

} // namespace backtrace
