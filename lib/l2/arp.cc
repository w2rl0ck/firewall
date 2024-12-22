#include <packet.h>
#include <arp.h>

namespace fw {

event_description_data arp_hdr::deserialize(packet &p, logging *log)
{
    event_description_data evt;

    if ((p.buf_len - p.off) < 0) {
        evt.set(event_type::EVENT_TYPE_DENY,
                event_description::EVENT_DESC_ARP_SHORT_LEN);
        return evt;
    }
    evt.set(event_type::EVENT_TYPE_ALLOW,
            event_description::EVENT_DESC_NONE);

    p.deserialize(hdr_type);
    p.deserialize(protocol_type);
    p.deserialize(hw_len);
    p.deserialize(protocol_len);
    p.deserialize(op);
    p.deserialize(sender_hw_addr, sizeof(sender_hw_addr));
    p.deserialize(sender_protocol_addr);
    p.deserialize(target_hw_addr, sizeof(target_hw_addr));
    p.deserialize(target_protocol_addr);

    if (hw_len != hw_len_default_) {
        evt.set(event_type::EVENT_TYPE_DENY,
                event_description::EVENT_DESC_ARP_HW_LEN_INVALID);
        return evt;
    }
    if (protocol_len != protocol_len_default_) {
        evt.set(event_type::EVENT_TYPE_DENY,
                event_description::EVENT_DESC_ARP_PROTOCOL_LEN_INVALID);
        return evt;
    }

    return evt;
}

int arp_hdr::serialize(packet &p, logging *log)
{
    p.serialize(hdr_type);
    p.serialize(protocol_type);
    p.serialize(hw_len);
    p.serialize(protocol_len);
    p.serialize(op);
    p.serialize(sender_hw_addr, sizeof(sender_hw_addr));
    p.serialize(sender_protocol_addr);
    p.serialize(target_hw_addr, sizeof(target_hw_addr));
    p.serialize(target_protocol_addr);

    return 0;
}

}
