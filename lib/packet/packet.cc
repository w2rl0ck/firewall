#include <cstdlib>
#include <cstring>

#include "packet.h"

namespace fw {

void packet::serialize(uint8_t val)
{
    buf_ptr[off] = val;

    off ++;
}

void packet::serialize(uint16_t val)
{
    buf_ptr[off + 1] = (val & 0x00FF);
    buf_ptr[off] = (val & 0xFF00) >> 8;

    off += 2;
}

void packet::serialize(uint32_t val)
{
    buf_ptr[off + 3] = (val & 0x000000FF);
    buf_ptr[off + 2] = (val & 0x0000FF00) >> 8;
    buf_ptr[off + 1] = (val & 0x00FF0000) >> 16;
    buf_ptr[off] = (val & 0xFF000000) >> 24;

    off += 4;
}

void packet::serialize(uint64_t val)
{
    buf_ptr[off] = (val & 0xFF00000000000000) >> 56;
    buf_ptr[off + 1] = (val & 0x00FF000000000000) >> 48;
    buf_ptr[off + 2] = (val & 0x0000FF0000000000) >> 40;
    buf_ptr[off + 3] = (val & 0x000000FF00000000) >> 32;
    buf_ptr[off + 4] = (val & 0x00000000FF000000) >> 24;
    buf_ptr[off + 5] = (val & 0x0000000000FF0000) >> 16;
    buf_ptr[off + 6] = (val & 0x000000000000FF00) >> 8;
    buf_ptr[off + 7] = (val & 0x00000000000000FF);

    off += 8;
}

void packet::serialize(uint8_t *val, size_t len)
{
    std::memcpy(buf_ptr + off, val, len);
    off += len;
}

int packet::alloc(uint32_t size)
{
    buf_ptr = (uint8_t *)calloc(1, size);
    if (!buf_ptr) {
        return -1;
    }

    return 0;
}

void packet::deserialize(uint8_t &val)
{
    val = buf_ptr[off];
    off ++;
}

void packet::deserialize(uint16_t &val)
{
    val = buf_ptr[off + 1] | (buf_ptr[off] << 8);
    off += 2;
}

void packet::deserialize(uint32_t &val)
{
    val = buf_ptr[off + 3] |
          (buf_ptr[off + 2] << 8) |
          (buf_ptr[off + 1] << 16) |
          (buf_ptr[off] << 24);
    off += 4;
}

void packet::deserialize(uint64_t &val)
{
    val = buf_ptr[off + 7] |
          (buf_ptr[off + 6] << 8) |
          (buf_ptr[off + 5] << 16) |
          (buf_ptr[off + 4] << 24) |
          ((uint64_t)(buf_ptr[off + 3]) << 32) |
          ((uint64_t)(buf_ptr[off + 2]) << 40) |
          ((uint64_t)(buf_ptr[off + 1]) << 48) |
          ((uint64_t)(buf_ptr[off]) << 56);
    off += 8;
}

void packet::deserialize(uint8_t *mac, size_t len)
{
    std::memcpy(mac, buf_ptr + off, len);
    off += len;
}

}
