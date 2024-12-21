#!/usr/bin/python3

import sys
import time

import scapy
import scapy.layers
import scapy.layers.l2
import scapy.sendrecv

## Defines ARP header configuration
class arp_gen_config:
    def __init__(self):
        self.hdr = scapy.layers.l2.ARP()
        self.iface = ""
        self.sender_mac = ""
        self.sender_ipaddr = ""
        self.tgt_mac = ""
        self.tgt_ipaddr = ""
        self.repeat_intvl_us = 0
        self.repeat_count = 3

class arp_gen:
    def __init__(self):
        self.ah = arp_gen_config()
        self.eh = scapy.layers.l2.Ether()
        self.src_mac = ""
        self.dst_mac = ""

    def set_config_params(self, iface, tgt_ipaddr, src_mac, dst_mac, repeat_intvl_us, repeat_count):
        self.iface = iface
        self.ah.tgt_ipaddr = tgt_ipaddr
        self.ah.hdr.pdst = tgt_ipaddr
        self.ah.repeat_intvl_us = repeat_intvl_us
        self.ah.repeat_count = repeat_count
        self.eh.src = src_mac
        self.eh.dst = dst_mac
        return self

    def send_arp(self):
        for i in range(self.ah.repeat_count):
            time.sleep(self.ah.repeat_intvl_us / 1000000)
            scapy.sendrecv.sendp(self.eh/self.ah.hdr, self.iface)

arp = arp_gen()
arp.set_config_params(sys.argv[1], "192.168.1.1", "00:01:02:02:03:04", "ff:ff:ff:ff:ff:ff", 1000 * 10, 100).send_arp()
