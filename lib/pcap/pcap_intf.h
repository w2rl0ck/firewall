/**
 * author: w2rl0ck
 * description:
 *     defines the pcap interface structures and writes and reads from interface.
*/
#ifndef __FW_PCAP_INTF_H__
#define __FW_PCAP_INTF_H__

#include <cstdint>
#include <string>

namespace fw {

/**
 * @brief - pcap write global header.
 */
typedef struct pcap_hdr_s {
    uint32_t magic_number;   /* magic number */
    uint16_t version_major;  /* major version number */
    uint16_t version_minor;  /* minor version number */
    int32_t  thiszone;       /* GMT to local correction */
    uint32_t sigfigs;        /* accuracy of timestamps */
    uint32_t snaplen;        /* max length of captured packets, in octets */
    uint32_t network;        /* data link type */
} pcap_hdr_t;

/**
 * @brief - packet header.
 */
typedef struct pcaprec_hdr_s {
    uint32_t ts_sec;         /* timestamp seconds */
    uint32_t ts_usec;        /* timestamp microseconds */
    uint32_t incl_len;       /* number of octets of packet saved in file */
    uint32_t orig_len;       /* actual length of packet */
} pcaprec_hdr_t;

/**
 * @brief - writer interface
 */
class pcap_writer {
    public:
        /**
         * @brief - create pcap writer.
         *
         * @param [in] filename - pcap filename
         */
        pcap_writer(const std::string &filename);
        ~pcap_writer();

        pcaprec_hdr_t format_pcap_pkthdr(size_t pktsize);
        int write_packet(pcaprec_hdr_t *rec, uint8_t *buf);
        /**
         * @brief - write pcap record.
         *
         * @param [in] buf - packet buffer
         * @param [in] buf_len - packet length
         *
         * @return 0 on success -1 on failure.
         */
        int write_packet(uint8_t *buf, uint32_t buf_len);

    private:
        FILE *fp;
        pcap_hdr_t format_default_glob_header();
};

/**
 * @brief - reader interface.
 */
class pcap_reader {
    public:
        /**
         * @brief - read pcap file and store header info.
         *
         * @param [in] filename - pcap filename.
         */
        pcap_reader(const std::string &filename);
        ~pcap_reader();

        /**
         * @brief - read a pcap record.
         *
         * @param [in] rec_hdr - pcap header.
         * @param [in] buf - buffer.
         * @param [in] buflen - buffer length.
         *
         * @return 0 on success -1 on failure.
         */
        int read_packet(pcaprec_hdr_t *rec_hdr, uint8_t *buf, size_t buflen);
    private:
        FILE *fp;
        pcap_hdr_t glob_hdr;
};

}

#endif

