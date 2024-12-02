/**
 * author: w2rl0ck
 * description:
 *     this file implements the creation and reception of firewall
 *     interface. The rx thread queues the frame to the packet queue.
*/
#include <time.h>
#include <sys/time.h>

#include <fw_config.h>
#include <fw_intf.h>
#include <packet.h>
#include <logging.h>

#define MAX_BUF_SIZE 1500

namespace fw {

/**
 * @brief - rx and queue frame.
*/
void fw_intf::rx_thread()
{
    int ret;

    while (1) {
        packet p;

        // alloc rx packet
        ret = p.alloc(MAX_BUF_SIZE);
        if (ret != 0) {
            break;
        }

        // rx frame
        ret = raw_->recv_msg(p.buf_ptr, MAX_BUF_SIZE);
        if (ret < 0) {
            continue;
        }
        p.buf_len = ret;

        {
            std::unique_lock l(q_lock_);
            q_cond_.notify_all();
            rx_q_.push(p);
        }
    }
}

/**
 * @brief - consume a packet and free up the buffer.
 */
void fw_intf::filter_func()
{
    //logging *log = logging::instance();

    while (1) {
        std::unique_lock l(q_lock_);
        q_cond_.wait(l);

        //log->info("waiting on packet from rx thread\n");
        int q_len = rx_q_.size();
        while (q_len > 0) {
            q_len --;
        }

        packet p = rx_q_.front();
        p.free_buf_ptr();
        rx_q_.pop();
    }
}

static int make_filename(std::string log_path,
                         const std::string &ifname,
                         std::string &filename)
{
    char filename_str[1024];
    struct tm *t;
    struct timespec tp;
    time_t now = time(0);
    int ret = -1;

    clock_gettime(CLOCK_REALTIME, &tp);

    t = gmtime(&now);
    if (t) {
        snprintf(filename_str, sizeof(filename_str),
                    "%s/pcap_log_%s_%04d_%02d_%02d_%02d_%02d_%02d_%04ld.pcap",
                    log_path.c_str(),
                    ifname.c_str(),
                    t->tm_year + 1900, t->tm_mon + 1,
                    t->tm_mday, t->tm_hour,
                    t->tm_min, t->tm_sec,
                    tp.tv_nsec / 1000000u);
        ret = 0;
        filename = filename_str;
    }

    return ret;
}

int fw_intf::create_pcap_file()
{
    fw_config *conf;
    std::string filename;
    int ret;

    conf = fw_config::instance();
    if (!conf->pcap_log_config_.enable) {
        return 0;
    }

    ret = make_filename(conf->pcap_log_config_.log_file_path, ifname_, filename);
    if (ret != 0) {
        return -1;
    }

    pcap_wr_ = std::make_shared<pcap_writer>(filename);
    log_->info("create pcap file <%s> ok.\n", filename.c_str());

    return 0;
}

int fw_intf::create(const std::string &ifname)
{
    int ret;

    ifname_ = ifname;

    raw_ = std::make_shared<raw_socket>(ifname, 0);

    log_->info("create raw socket on <%s>\n", ifname_.c_str());

    ret = create_pcap_file();
    if (ret < 0) {
        log_->error("failed to create pcap file for <%s>\n", ifname_.c_str());
        return -1;
    }

    rx_thr_ = std::make_unique<std::thread>(&fw_intf::rx_thread, this);
    rx_thr_->detach();

    log_->info("create rx thread ok\n");

    filt_thr_ = std::make_unique<std::thread>(&fw_intf::filter_func, this);
    filt_thr_->detach();

    log_->info("create filter thread ok\n");

    return 0;
}

fw_intf::fw_intf(logging *log)
{
    log_ = log;
}

fw_intf::~fw_intf()
{

}

}
