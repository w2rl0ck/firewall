cmake_minimum_required(VERSION 3.9)

project(firewall)

set(LIB_SRC
    ./lib/packet/packet.cc
    ./lib/raw/raw_socket.cc
    ./lib/log/logging.cc
    ./lib/pcap/pcap_intf.cc
    ./lib/l2/eth.cc
    ./lib/common/clock_info.cc)

set(FW_SRC
    src/base/fw_base.cc
    src/base/fw_intf.cc
    src/base/fw_cmd_args.cc
    src/base/fw_config.cc
    src/filter/fw_filter.cc
    src/events/event_store.cc
    src/events/event_info.cc
    src/events/event_log.cc)

set(SRC
    ${LIB_SRC}
    ${FW_SRC})

include_directories(
    ./lib/common/
    ./lib/packet/
    ./lib/pcap/
    ./lib/log/
    ./lib/raw/
    ./src/base/
    ./src/filter/
    ./src/events/
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter -g -ggdb -Os")

add_executable(fwd ${SRC})
target_link_libraries(fwd jsoncpp pthread)
