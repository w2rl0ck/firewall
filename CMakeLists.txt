cmake_minimum_required(VERSION 3.9)

set(LIB_SRC
    ./lib/packet/packet.cc)

set(FW_SRC
    src/base/fw_base.cc
    src/base/fw_intf.cc)

set(SRC
    ${LIB_SRC}
    ${FW_SRC})

include_directories(
    ./lib/packet/
    ./src/base/
)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-parameter")

add_executable(fwd ${SRC})
target_link_libraries(fwd pthread)
