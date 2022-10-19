#!/usr/bin/python3

from bcc import BPF

b = BPF(src_file='tracepoint_probe.c')

print("%-18s %-18s %-6s %-6s %-6s" % ("TIME(s)", "COMM", "PID", "GOTBITS", "INPUT_LEFT"))

while 1:
    try:
        (task, pid, cpu, flags, ts, msg) = b.trace_fields()
        (got_bits, input_left) = msg.decode().split(" ")
    except ValueError:
        continue
    print("%-18.9f %-18s %-6s %-6s %-6s" % (ts, task, pid, got_bits, input_left))
