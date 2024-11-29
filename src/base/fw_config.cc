#include <fstream>

#include "json/json.h"

#include <fw_config.h>
#include <logging.h>

namespace fw {

int fw_events::parse(Json::Value &r)
{
    forward_events  = r["forward_events"].asBool();
    log_events      = r["log_events"].asBool();
    log_file_path   = r["log_file_path"].asString();

    return 0;
}

int fw_log_pcap::parse(Json::Value &r)
{
    enable              = r["enable"].asBool();
    log_file_path       = r["log_file_path"].asString();

    return 0;
}

void fw_config::print()
{
    logging *log = logging::instance();

    for (auto it : intf_config_) {
        log->info("fw_intf_info:\n");
        log->info("\t ifname: %s\n", it.ifname.c_str());
        log->info("\t rule_file: %s\n", it.rule_file.c_str());
    }

    log->info("events:\n");
    log->info("\t forward_events: %d\n", event_config_.forward_events);
    log->info("\t log_events: %d\n", event_config_.log_events);
    log->info("\t log_file_path: %s\n", event_config_.log_file_path.c_str());

    log->info("pcap:\n");
    log->info("\t enable: %d\n", pcap_log_config_.enable);
    log->info("\t log_file_path: %s\n", pcap_log_config_.log_file_path.c_str());
}

int fw_config::parse(const std::string &config)
{
    Json::Value root;
    std::ifstream conf(config, std::ifstream::binary);

    conf >> root;

    for (auto it : root["fw_intf_info"]) {
        fw_intf_info intf_info;

        intf_info.ifname = it["interface_name"].asString();
        intf_info.rule_file = it["rules_file"].asString();

        intf_config_.push_back(intf_info);
    }

    event_config_.parse(root["events"]);
    pcap_log_config_.parse(root["pcap"]);

    //print();

    return 0;
}

}
