/**
 * author: w2rl0ck
 * description:
 *    defines a firewall interface class.
*/
#ifndef __FW_INTF_H__
#define __FW_INTF_H__

#include <string>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <raw_socket.h>
#include <packet.h>
#include <pcap_intf.h>
#include <logging.h>

namespace fw {

/**
 * @brief - defines a firewall interface.
*/
class fw_intf {
    public:
        explicit fw_intf(logging *log);
        ~fw_intf();

        /**
         * @brief - create a firewall interface context.
         *
         * @param [in] ifname - interface name.
        */
        int create(const std::string &ifname);

    private:
        logging *log_;
        std::string ifname_;
        std::queue<packet> rx_q_;
        std::mutex q_lock_;
        std::condition_variable q_cond_;
        /* one rx thread per interface. */
        std::unique_ptr<std::thread> rx_thr_;
        std::shared_ptr<raw_socket> raw_;
        std::shared_ptr<pcap_writer> pcap_wr_;

        void rx_thread();
        int create_pcap_file();
};

}

#endif

