# hello

## compile

```shell
$ make libbpf
$ make vmliunx
$ make 
$ ./hello
Successfully started! Tracing /sys/kernel/debug/tracing/trace_pipe...
              sh-245801  [001] d...1 223410.354747: bpf_trace_printk: Process[245801]: /bin/sh

              sh-245801  [000] d...1 223410.355144: bpf_trace_printk: Process[245801]: return: 0

           <...>-245802  [001] d...1 223410.357126: bpf_trace_printk: Process[245802]: /usr/bin/cat

           <...>-245802  [001] d...1 223410.357284: bpf_trace_printk: Process[245802]: return: 0
```

## 原理分析

该程序通过静态跟踪的方式在sys_enter_execve、sys_exit_execve系统调用时获取当前执行进程的pid和进程名称以及返回值,并将获取到的信息打印到系统调试信息中；

## 查询系统调用静态跟踪点

```shell
$ bpftrace -l 'tracepoint:syscalls:*'
```

## 查询某个系统调用函数参数

```shell
$ bpftrace -lv 'tracepoint:syscalls:sys_enter_execve'
tracepoint:syscalls:sys_enter_execve
    int __syscall_nr;
    const char * filename;
    const char *const * argv;
    const char *const * envp;
```

通过上述入口系统调用函数的参数就可以获取到第一个参数为进程名称，第二个参数为进程的执行参数指针;
同理可以在出口系统调用处获取返回值;
