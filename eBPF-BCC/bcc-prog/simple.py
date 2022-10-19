from __future__ import print_function

import sys
from time import sleep, strftime

from bcc import BPF


bpf_text = """
#include <uapi/linux/ptrace.h>
#include <linux/blkdev.h>

BPF_HASH(start, struct request *);
BPF_HISTOGRAM(dist);

// time block I/O
int trace_req_start(struct pt_regs *ctx, struct request *req)
{
    u64 ts = bpf_ktime_get_ns();
    start.update(&req, &ts);
    return 0;
}

// output
int trace_req_done(struct pt_regs *ctx, struct request *req)
{
    u64 *tsp, delta;

    // fetch timestamp and calculate delta
    tsp = start.lookup(&req);
    if (tsp == 0) {
        return 0;   // missed issue
    }
    delta = bpf_ktime_get_ns() - *tsp;
    delta /= 1000;

    // store as histogram
    dist.increment(bpf_log2l(delta));

    start.delete(&req);
    return 0;
}
"""

b = BPF(text=bpf_text)
if BPF.get_kprobe_functions(b'blk_start_request'):
    b.attach_kprobe(event="blk_start_request", fn_name="trace_req_start")
    b.attach_kprobe(event="blk_mq_start_request", fn_name="trace_req_start")
    b.attach_kprobe(event="blk_account_io_done", fn_name="trace_req_done")

if len(sys.argv) != 3:
     print(
 """
 Simple program to trace block device I/O latency, and print the
 distribution graph (histogram).

 Usage: %s [interval] [count]

 interval - recording period (seconds)
 count - how many times to record

 Example: print 1 second summaries, 10 times
 $ %s 1 10
 """ % (sys.argv[0], sys.argv[0]))
     sys.exit(1)

interval = int(sys.argv[1])
countdown = int(sys.argv[2])
print("Tracing block device I/O... Hit Ctrl-C to end.")

exiting = 0 if interval else 1
dist = b.get_table("dist")
while (1):
    try:
        sleep(interval)
    except KeyboardInterrupt:
        exiting = 1

    print()
    print("%-8s\n" % strftime("%H:%M:%S"), end="")

    dist.print_log2_hist("usecs", "disk")
    dist.clear()

    countdown -= 1
    if exiting or countdown == 0:
        exit()
