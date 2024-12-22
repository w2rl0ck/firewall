#include <eth.h>
#include <ether_types.h>
#include <event_store.h>

#include <fw_filter.h>

namespace fw {

int fw_filter::l2_parse(packet &p)
{
    logging *log;
    event_description_data evt;

    log = logging::instance();

    evt = eh.deserialize(p, log);
    //eh.print(log);
    if (evt.type == event_type::EVENT_TYPE_DENY) {
        return -1;
    }

    switch (static_cast<ether_types>(eh.ethertype)) {
    }

    return 0;
}

int fw_filter::run(packet &p)
{
    int ret;

    ret = l2_parse(p);

    return ret;
}

}
