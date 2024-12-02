cmake_minimum_required(VERSION 3.9)

set(LIB_SRC
    ./lib/packet/packet.cc
    ./lib/raw/raw_socket.cc
    ./lib/log/logging.cc
    ./lib/pcap/pcap_intf.cc)

set(FW_SRC
    src/base/fw_base.cc
    src/base/fw_intf.cc
    src/base/fw_cmd_args.cc
    src/base/fw_config.cc)

set(SRC
    ${LIB_SRC}
    ${FW_SRC})

include_directories(
    ./lib/packet/
    ./lib/pcap/
    ./lib/log/
    ./lib/raw/
    ./src/base/
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter -g -ggdb -Os")

add_executable(fwd ${SRC})
target_link_libraries(fwd jsoncpp pthread)
