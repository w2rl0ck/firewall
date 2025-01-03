cmake_minimum_required(VERSION 3.9)

project(firewall)

file(GLOB L2_LIB_SRC
    ./lib/l2/*.cc)

set(LIB_SRC
    ./lib/packet/packet.cc
    ./lib/raw/raw_socket.cc
    ./lib/log/logging.cc
    ./lib/pcap/pcap_intf.cc
    ${L2_LIB_SRC}
    ./lib/common/clock_info.cc
    ./src/events/event_store.cc
    ./src/events/event_info.cc
    ./src/events/event_log.cc)

set(FW_SRC
    src/base/fw_base.cc
    src/base/fw_intf.cc
    src/base/fw_cmd_args.cc
    src/base/fw_config.cc
    src/filter/fw_filter.cc)

set(SRC
    ${LIB_SRC}
    ${FW_SRC})

set(PKTGEN_SRC
    ./testing/pkt_gen/pkt_gen_conf.cc
    ./testing/pkt_gen/pkt_gen_eth.cc
    ./testing/pkt_gen/pkt_gen_host_scan.cc
    ./testing/pkt_gen/pkt_gen_pcap_replay.cc
    ./testing/pkt_gen/pkt_gen.cc
    ${LIB_SRC})

include_directories(
    ./lib/common/
    ./lib/packet/
    ./lib/pcap/
    ./lib/l2/
    ./lib/log/
    ./lib/raw/
    ./src/base/
    ./src/filter/
    ./src/events/
    ./testing/pkt_gen/
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter -g -ggdb -Os")

add_executable(fwd ${SRC})
target_link_libraries(fwd jsoncpp pthread)

add_executable(pkt_gen ${PKTGEN_SRC})
target_link_libraries(pkt_gen jsoncpp pthread)
