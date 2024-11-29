#ifndef __FW_CMD_ARGS_H__
#define __FW_CMD_ARGS_H__

#include <string>
#include <logging.h>

namespace fw {

struct fw_cmd_args {
    std::string config_file;

    static fw_cmd_args *instance() {
        static fw_cmd_args cmd_args;
        return &cmd_args;
    }

    int parse(int argc, char **argv, logging *log);

    private:
        explicit fw_cmd_args() { }
};

}

#endif

