/**
 * @brief - Defines raw socket.
 *
 * @copyright - 2024-present All rights reserved.
 */
#ifndef __FW_RAW_SOCKET_H__
#define __FW_RAW_SOCKET_H__

#include <cstdint>
#include <string>

namespace fw {

/**
 * @brief - Implements raw socket
 */
class raw_socket {
    public:
        /**
         * @brief - Create raw socket object.
         *
         * @param [in] - dev Interface name (shown in ifconfig).
         * @param [in] - ethertype Set 0 as default.
         *
         * This constructor will throw exception.
         */
        explicit raw_socket(const std::string dev, uint16_t ethertype);
        ~raw_socket();
        /**
         * @brief - Get socket from the raw socket object.
         *
         * @return socket id on success.
         * @return -1 on failure.
         */
        int get_socket() const noexcept;

        int send_msg(const uint8_t *mac, uint16_t ethertype, uint8_t *data, size_t data_len) noexcept;
        /**
         * @brief - Send message via the raw socket.
         *
         * @param [in] - dest Destination mac address.
         * @param [in] - data Transmit buffer.
         * @param [in] - data_len Transmit buffer length.
         *
         * @return Length of transmitted data on success.
         * @return -1 on failure.
         */
        int send_msg(const uint8_t *dest, uint8_t *data, size_t data_len) noexcept;
        int recv_msg(uint8_t *mac, uint16_t &ethertype, uint8_t *data, size_t data_len) noexcept;

        /**
         * @brief - Receive message via the raw socket.
         *
         * @param [in] - mac Sender's mac address.
         * @param [in] - data Receive buffer.
         * @param [in] - data_len Length of received buffer.
         *
         * @return Length of received data on success.
         * @return -1 on failure.
         */
        int recv_msg(uint8_t *mac, uint8_t *data, size_t data_len) noexcept;

        /**
         * @brief - Receive message via the raw socket.
         *
         * @param [out] data - rx pkt buffer.
         * @param [in] data_len - length of the rx pkt buffer.
         *
         * @return Length of received data on success.
         * @return -1 on failure.
         */
        int recv_msg(uint8_t *data, size_t data_len) noexcept;
    private:
        int fd_;
        std::string dev_;
        int ifindex_;
        uint8_t devmac_[6];
};

}

#endif

