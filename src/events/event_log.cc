#include "fw_config.h"
#include "event_log.h"

namespace fw {

int event_log::create()
{
    fw_config *conf = fw_config::instance();

    if (conf->event_config_.log_events) {
        log_thread_ = std::make_unique<std::thread>(&event_log::logging_thread, this);
    }

    return 0;
}

void event_log::logging_thread()
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void event_log::queue_event(event_information &info)
{
    std::unique_lock l(lock_);
}

}
