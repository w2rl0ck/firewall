#include <iostream>

#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include <logging.h>

namespace fw {

static void log_msg(const char *fmt, const char *lvl, va_list ap)
{
    char msg[1024];
    struct tm *t;
    time_t now = time(0);
    struct timespec tp;
    int len;

    clock_gettime(CLOCK_REALTIME, &tp);

    t = gmtime(&now);
    if (t) {
        len = snprintf(msg, sizeof(msg),
                 "[%04d-%02d-%02d  %02d:%02d:%02d.%04ld]: <%s> ",
                 t->tm_year + 1900, t->tm_mon + 1,
                 t->tm_mday, t->tm_hour,
                 t->tm_min, t->tm_sec,
                 tp.tv_nsec / 1000000u, lvl);
        len += vsnprintf(msg + len, sizeof(msg) - len, fmt, ap);
    }
    fprintf(stderr, "%s", msg);
}

void logging::info(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_msg(fmt, "info", ap);
    va_end(ap);
}

void logging::warn(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_msg(fmt, "warn", ap);
    va_end(ap);
}

void logging::error(const char *fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    log_msg(fmt, "error", ap);
    va_end(ap);
}

}
