#include <getopt.h>

#include <fw_cmd_args.h>
#include <logging.h>

namespace fw {

static void usage(const char *progname, logging *log)
{
    log->info("%s <-f>\n"
              "\t\t\t\t\t -f : configuration file\n",
              progname);
}

int fw_cmd_args::parse(int argc, char **argv, logging *log)
{
    int ret;

    if (argc == 1) {
        usage(argv[0], log);
        return -1;
    }

    while ((ret = getopt(argc, argv, "f:")) != -1) {
        switch (ret) {
            case 'f':
                config_file = std::string(optarg);
            break;
            default:
                usage(argv[0], log);
                return -1;
        }
    }

    return 0;
}

}
