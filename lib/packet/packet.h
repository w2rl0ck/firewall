#ifndef __FW_PACKET_H__
#define __FW_PACKET_H__

#include <string>
#include <cstdint>
#include <cstdlib>

#include <clock_info.h>

namespace fw {

/**
 * @brief - holds a packet and implements series of operations on the packet.
*/
struct packet {
    std::string         ifname;
    uint8_t             *buf_ptr;
    uint32_t            buf_len;
    timestamp_data      arrival_ts;
    uint32_t            off;

    explicit packet() : buf_ptr(nullptr), buf_len(0), off(0){ }
    ~packet() { }

    void serialize(uint8_t val);
    void serialize(uint8_t *val, size_t len);
    void serialize(uint16_t val);
    void serialize(uint32_t val);
    void serialize(uint64_t val);
    void deserialize(uint8_t &val);
    void deserialize(uint8_t *val, size_t len);
    void deserialize(uint16_t &val);
    void deserialize(uint32_t &val);
    void deserialize(uint64_t &val);
    int alloc(uint32_t size);
    bool has_alloc() { return buf_ptr != nullptr; }
    void free_buf_ptr() {
        if (buf_ptr != nullptr) {
            free(buf_ptr);
        } 
    }
};

}

#endif
