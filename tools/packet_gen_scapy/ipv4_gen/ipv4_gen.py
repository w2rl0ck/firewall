#!/usr/bin/python3

import sys
import time

import scapy
import scapy.layers
import scapy.layers.l2
import scapy.layers.inet
import scapy.sendrecv

class ipv4_gen_config:
    def __init__(self):
        self.hdr = scapy.layers.inet.IP()
        self.eh = scapy.layers.l2.Ether()
        self.ifname = ""

    def set_config(self, ifname):
        self.ifname = ifname

    def get_ip_hdr(self):
        return self.hdr

class ipv4_gen:
    def __init__(self, conf : ipv4_gen_config):
        self.conf = conf

    def send(self):
        scapy.sendrecv.sendp(self.conf.eh/self.conf.hdr, self.conf.ifname)

v4_conf = ipv4_gen_config()
v4_conf.ifname = sys.argv[1]

v4_pkt_gen = ipv4_gen(v4_conf)
v4_pkt_gen.send()

