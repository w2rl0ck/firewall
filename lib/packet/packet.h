#ifndef __FW_PACKET_H__
#define __FW_PACKET_H__

#include <cstdint>

namespace fw {

struct packet {
    uint8_t *buf_ptr;
    uint32_t buf_len;
    uint32_t off;

    explicit packet() : buf_ptr(nullptr), buf_len(0), off(0){ }
    ~packet() { }

    void serialize(uint8_t val);
    void serialize(uint16_t val);
    void serialize(uint32_t val);
    void serialize(uint64_t val);
    int alloc(uint32_t size);
};

}

#endif
