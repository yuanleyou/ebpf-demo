int kprobe__sys_sync(void *ctx)
{
	bpf_trace_printk("sys_sync() called\n");
	return 0;
}
