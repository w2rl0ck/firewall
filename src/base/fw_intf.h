#ifndef __FW_INTF_H__
#define __FW_INTF_H__

#include <string>
#include <memory>
#include <thread>

namespace fw {

class fw_intf {
    public:
        explicit fw_intf();
        ~fw_intf();

        int create(const std::string &ifname);

    private:
        std::string ifname_;
        /* one rx thread per interface. */
        std::unique_ptr<std::thread> rx_thr_;

        void rx_thread();
};

}

#endif

