#ifndef __FW_EVENTS_EVENT_STORE_H__
#define __FW_EVENTS_EVENT_STORE_H__

#include <string>
#include <map>
#include <vector>
#include <mutex>
#include <event_info.h>

namespace fw {

class event_store {
    public:
        ~event_store() { }
        static event_store *instance() {
            static event_store es;
            return &es;
        }

        void write_event(std::string &ifname, event_information &info);
        void write_event(std::string &ifname,
                         timestamp_data &arrival_ts,
                         event_type type,
                         event_description desc);

    private:
        explicit event_store() { }

        std::map<std::string, event_information> event_map_store_;
        std::mutex lock_;
};

}

#endif
