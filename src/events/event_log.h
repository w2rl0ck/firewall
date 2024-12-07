#ifndef __FW_EVENTS_EVENT_LOG_H__
#define __FW_EVENTS_EVENT_LOG_H__

#include <memory>
#include <thread>
#include <mutex>
#include <queue>

#include "event_info.h"

namespace fw {

class event_log {
    public:
        ~event_log() { }
        static event_log *instance() {
            static event_log log;
            return &log;
        }

        int create();
        void queue_event(event_information &info);
    private:
        explicit event_log() { }
        void logging_thread();

        std::unique_ptr<std::thread> log_thread_;
        std::string log_file_name_;
        std::queue<event_information> evt_info_queue_;
        std::mutex lock_;
};

}

#endif

