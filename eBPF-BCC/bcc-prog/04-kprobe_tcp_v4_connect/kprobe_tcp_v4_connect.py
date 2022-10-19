#!/usr/bin/python3

from __future__ import print_function
from bcc import BPF

b = BPF(src_file='kprobe_tcp_v4_connect.c')

# header
print("%-6s %-12s %-16s %-16s %-4s" % ("PID", "COMM", "SADDR", "DADDR",
    "DPORT"))

def inet_ntoa(addr):
    dq = ''
    for i in range(0, 4):
        dq = dq + str(addr & 0xff)
        if (i != 3):
            dq = dq + '.'
        addr = addr >> 8
    return dq

# filter and format output
while 1:
    # Read messages from kernel pipe
    try:
        (task, pid, cpu, flags, ts, msg) = b.trace_fields()
        (_tag, netns_hs, daddr_hs, dport_s) = msg.decode().split(" ")
    except ValueError:
        # Ignore messages from other tracers
        continue

    # Ignore messages from other tracers
    if _tag != "trace_tcp4connect":
        continue

    print("%-6d %-12.12s %-16s %-16s %-4s" % (pid, task,
	    inet_ntoa(int(netns_hs, 16)),
	    inet_ntoa(int(daddr_hs, 16)),
	    dport_s))
