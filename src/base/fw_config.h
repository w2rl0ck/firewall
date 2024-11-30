#ifndef __FW_CONFIG_H__
#define __FW_CONFIG_H__

#include <string>
#include <vector>

#include "json/json.h"

namespace fw {

struct fw_intf_info {
    std::string ifname;
    std::string rule_file;

    int parse(Json::Value &r);
};

struct fw_events {
    bool forward_events;
    bool log_events;
    std::string log_file_path;

    int parse(Json::Value &r);
};

struct fw_log_pcap {
    bool enable;
    std::string log_file_path;

    int parse(Json::Value &r);
};

struct fw_config {
    public:
        std::vector<fw_intf_info> intf_config_;
        fw_events event_config_;
        fw_log_pcap pcap_log_config_;

        static fw_config *instance() {
            static fw_config conf;
            return &conf;
        }

        /**
         * @brief - parse configuration.
        */
        int parse(const std::string &config);
        ~fw_config() { }

    private:
        explicit fw_config() { }
        void print();
};

}

#endif

