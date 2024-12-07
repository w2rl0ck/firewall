#include "eth.h"

#include "event_info.h"

namespace fw {

int eth_hdr::serialize(packet *pkt, logging *log)
{
    pkt->serialize(dst, sizeof(dst));
    pkt->serialize(src, sizeof(src));
    pkt->serialize(ethertype);

    return 0;
}

int eth_hdr::deserialize(packet *pkt, logging *log)
{
    if (pkt->buf_len < len_) {
        return -1;
    }

    pkt->deserialize(dst, sizeof(dst));
    pkt->deserialize(src, sizeof(src));
    pkt->deserialize(ethertype);

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

}
