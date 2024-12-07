#include <time.h>
#include <sys/time.h>

#include "clock_info.h"

namespace fw {

void timestamp_data::now()
{
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);
    sec = tp.tv_sec;
    nsec = tp.tv_nsec;
}

}
