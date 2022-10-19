#!/usr/bin/python3

from bcc import BPF

b = BPF(src_file='hello_fields.c')

b.attach_kprobe(event=b.get_syscall_fnname("clone"), fn_name="hello")

print("%-18s %-16s %-6s %s" % ("TIME(s)", "COMM", "PID", "MESSAGE"))

while(1):
    try:
        (task, pid, cpu, flags, timestamp, msg) = b.trace_fields()
    except ValueError:
        continue
    print("%-18.9f %-16s %-6d %s" % (timestamp, task, pid, msg))
