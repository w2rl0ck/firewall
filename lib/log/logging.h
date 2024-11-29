#ifndef __FW_LOGGING_H__
#define __FW_LOGGING_H__

namespace fw {

class logging {
    public:
        static logging *instance() {
            static logging log;
            return &log;
        }

        void info(const char *fmt, ...);
        void warn(const char *fmt, ...);
        void error(const char *fmt, ...);

        ~logging() { }
    private:
        explicit logging() { }
};

}

#endif
