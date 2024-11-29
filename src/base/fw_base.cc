#include <fw_base.h>

namespace fw {

int fw_base::init(int argc, char **argv)
{
    logging *log;
    fw_config *conf;
    fw_cmd_args *cmd_args;
    int ret;

    log = logging::instance();

    cmd_args = fw_cmd_args::instance();
    ret = cmd_args->parse(argc, argv, log);
    if (ret != 0) {
        log->error("failed to parse command line args\n");
        return -1;
    }

    log->info("parse command line args ok\n");

    conf = fw_config::instance();
    ret = conf->parse(cmd_args->config_file);
    if (ret != 0) {
        log->error("failed to parse configuration %s\n", cmd_args->config_file);
        return -1;
    }

    log->info("parse configuration ok\n");

    for (auto it : conf->intf_config_) {
        std::shared_ptr<fw_intf> intf;

        intf = std::make_shared<fw_intf>(log);
        ret = intf->create(it.ifname);
        if (ret != 0) {
            ret = -1;
            break;
        }

        intf_list_.push_back(intf);
    }

    log->info("init firewall daemon ok\n");

    return ret;
}

void fw_base::run()
{
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

}

int main(int argc, char **argv)
{
    fw::fw_base base;
    int ret;

    ret = base.init(argc, argv);
    if (ret < 0) {
        return -1;
    }

    base.run();

    return 0;
}
