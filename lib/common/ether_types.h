#ifndef __FW_LIB_ETHER_TYPES_H__
#define __FW_LIB_ETHER_TYPES_H__

#include <cstdint>

namespace fw {

enum class ether_types : uint32_t {
    ETHER_TYPE_ARP      = 0x0806,
    ETHER_TYPE_IPV4     = 0x0800,
};

}

#endif

