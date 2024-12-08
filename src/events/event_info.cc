#include <event_info.h>

namespace fw {

void event_information::set(std::string &ifname,
                            timestamp_data &arrival_ts,
                            event_type type,
                            event_description desc)
{
    ifname = ifname;
    pkt_arrival_ts = arrival_ts;
    evt_type = type;
    evt_desc = desc;
}

}

