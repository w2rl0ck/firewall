#include "fw_config.h"
#include "event_store.h"
#include "event_log.h"

namespace fw {

void event_store::write_event(std::string &ifname, event_information &info)
{
    fw_config *conf;

    conf = fw_config::instance();

    if (conf->event_config_.log_events) {
        event_log *log = event_log::instance();

        log->queue_event(info);
    }

    std::unique_lock l(lock_);
    event_map_store_.insert(std::pair(ifname, info));
}

void event_store::write_event(std::string &ifname,
                              timestamp_data &arrival_ts,
                              event_type type,
                              event_description desc)
{
    event_information info;

    info.set(ifname, arrival_ts, type, desc);
    write_event(ifname, info);
}

}

