#include <net/net_namespace.h>
#include <bcc/proto.h>
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wenum-conversion"
#include <net/inet_sock.h>
#pragma clang diagnostic pop

// At the begining of the C program, declare our event
struct listen_evt_t {
    u64 laddr;
    u64 lport;
    u64 netns;
    u64 backlog;
};
BPF_PERF_OUTPUT(listen_evt);

// In kprobe__inet_listen, replace the printk with
struct listen_evt_t evt = {
    .laddr = ntohl(laddr),
    .lport = ntohs(lport),
    .netns = netns,
    .backlog = backlog,
};
listen_evt.perf_submit(ctx, &evt, sizeof(evt));
