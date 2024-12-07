#ifndef __FW_LIB_COMMON_CLOCK_INFO_H__
#define __FW_LIB_COMMON_CLOCK_INFO_H__

#include <cstdint>

namespace fw {

struct timestamp_data {
    uint64_t nsec;
    uint32_t sec;

    explicit timestamp_data() : nsec(0), sec(0) { }
    ~timestamp_data() { }

    void now();
};

}

#endif

