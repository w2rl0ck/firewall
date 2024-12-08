#include <eth.h>
#include <ether_types.h>
#include <event_store.h>

#include <fw_filter.h>

namespace fw {

int fw_filter::l2_parse(packet &p)
{
    logging *log;
    int ret;

    log = logging::instance();

    ret = eh.deserialize(p, log);
    //eh.print(log);
    if (ret != 0) {
        return -1;
    }

    switch (static_cast<ether_types>(eh.ethertype)) {
    }

    return ret;
}

int fw_filter::run(packet &p)
{
    int ret;

    ret = l2_parse(p);

    return ret;
}

}
