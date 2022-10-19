TRACEPOINT_PROBE(random, urandom_read) {
	// agrs is from /sys/kernel/debug/tracing/events/random/urandom_read/format
	bpf_trace_printk("%d %d\n", args->got_bits, args->input_left);
	return 0;
};
