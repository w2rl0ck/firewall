#ifndef __FW_FILTER_H__
#define __FW_FILTER_H__

#include <eth.h>

#include <packet.h>

#include <logging.h>

namespace fw {

class fw_filter {
    public:
        explicit fw_filter() { }
        ~fw_filter() { }

        int run(packet &p);

    private:
        int l2_parse(packet &p);

        packet p;
        eth_hdr eh;
};

}

#endif
