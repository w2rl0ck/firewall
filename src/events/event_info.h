#ifndef __FW_EVENTS_EVENT_INFO_H__
#define __FW_EVENTS_EVENT_INFO_H__

#include <string>
#include <clock_info.h>

namespace fw {

enum class event_type {
    EVENT_TYPE_ALLOW,
    EVENT_TYPE_DENY,
};

enum class event_description : uint32_t {
    EVENT_DESC_ETH_BROADCAST_DA             = 0x1000,
    EVENT_DESC_ETH_BROADCAST_SA,
    EVENT_DESC_ETH_UNSUPPORTED_ETHERTYPE,
    EVENT_DESC_ETH_SHORT_LEN,

    EVENT_DESC_ARP_SHORT_LEN                = 0x2000,
    EVENT_DESC_ARP_HW_LEN_INVALID,
    EVENT_DESC_ARP_PROTOCOL_LEN_INVALID,

    EVENT_DESC_NONE                         = 0xFFFFFFFE,
};

struct event_description_data {
    event_type type;
    event_description desc;

    void set(event_type t, event_description d) { type = t, desc = d; }
};

struct event_information {
    std::string         ifname;
    timestamp_data      pkt_arrival_ts;
    timestamp_data      event_ts;
    event_type          evt_type;
    event_description   evt_desc;

    explicit event_information() :
            ifname(""),
            evt_type(event_type::EVENT_TYPE_DENY),
            evt_desc(event_description::EVENT_DESC_NONE)
    { }
    ~event_information() { }

    void set(std::string &ifname,
             timestamp_data &arrival_ts,
             event_type evt_type,
             event_description evt_desc);
};

}

#endif
