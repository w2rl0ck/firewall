#include <fw_intf.h>

namespace fw {

void fw_intf::rx_thread()
{

}

int fw_intf::create(const std::string &ifname)
{
    ifname_ = ifname;

    rx_thr_ = std::make_unique<std::thread>(&fw_intf::rx_thread, this);
    rx_thr_->detach();

    return 0;
}

}
