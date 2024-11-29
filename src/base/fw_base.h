#ifndef __FW_BASE_H__
#define __FW_BASE_H__

#include <string>
#include <vector>

#include <fw_cmd_args.h>
#include <fw_config.h>
#include <fw_intf.h>
#include <logging.h>

namespace fw {

/**
 * @brief - defines the base class of firewall.
*/
class fw_base {
    public:
        explicit fw_base() { }
        ~fw_base() { }

        int init(int argc, char **argv);
        void run();

    private:
        std::vector<std::shared_ptr<fw_intf>> intf_list_;
};

}

#endif
