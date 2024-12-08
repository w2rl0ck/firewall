/**
 * @brief - implements ethernet serialize deserialize.
 * @author - w2rl0ck.
 * @copyright - see LICENSE all rights reserved.
 */
#include <cstring>

#include "eth.h"
#include "event_info.h"
#include "event_store.h"

namespace fw {

int eth_hdr::serialize(packet &pkt, logging *log)
{
    pkt.serialize(dst, sizeof(dst));
    pkt.serialize(src, sizeof(src));
    pkt.serialize(ethertype);

    return 0;
}

int eth_hdr::deserialize(packet &pkt, logging *log)
{
    if (pkt.buf_len < len_) {
        event_store *store;

        store = event_store::instance();
        store->write_event(pkt.ifname,
                           pkt.arrival_ts,
                           event_type::EVENT_TYPE_DENY,
                           event_description::EVENT_DESC_ETH_SHORT_LEN);
        return -1;
    }

    pkt.deserialize(dst, sizeof(dst));
    pkt.deserialize(src, sizeof(src));
    pkt.deserialize(ethertype);

    return 0;
}

void eth_hdr::print(logging *log)
{
    log->info("eth: {\n");
    log->info("\t dst: %02x:%02x:%02x:%02x:%02x:%02x\n",
                            dst[0], dst[1], dst[2],
                            dst[3], dst[4], dst[5]);
    log->info("\t src: %02x:%02x:%02x:%02x:%02x:%02x\n",
                            src[0], src[1], src[2],
                            src[3], src[4], src[5]);
    log->info("\t ethertype: 0x%04x\n", ethertype);
    log->info("}\n");
}

bool eth_hdr::is_broadcast_mac(uint8_t *mac)
{
    uint8_t bmac[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    return std::memcmp(mac, bmac, 6) == 0;
}

}
