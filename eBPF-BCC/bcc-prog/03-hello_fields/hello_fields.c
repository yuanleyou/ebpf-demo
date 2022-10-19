int hello(void *ctx)
{
	bpf_trace_printk("hello world\n");
	return 0;
}
