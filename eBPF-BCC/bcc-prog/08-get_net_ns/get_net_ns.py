#!/usr/bin/python3
# We need ctypes to parse the event structure
import ctypes
from bcc import BPF

# Declare data format
class ListenEvt(ctypes.Structure):
    _fields_ = [
        ("laddr",   ctypes.c_ulonglong),
        ("lport",   ctypes.c_ulonglong),
        ("netns",   ctypes.c_ulonglong),
        ("backlog", ctypes.c_ulonglong),
    ]

# Declare event printer
def print_event(cpu, data, size):
    event = ctypes.cast(data, ctypes.POINTER(ListenEvt)).contents
    print("Listening on %x %d with %d pending connections in container %d" % (
        event.laddr,
        event.lport,
        event.backlog,
        event.netns,
    ))

b = BPF(src_file='get_net_ns.c')

# Replace the event loop
b["listen_evt"].open_perf_buffer(print_event)
while True:
    b.kprobe_poll()
