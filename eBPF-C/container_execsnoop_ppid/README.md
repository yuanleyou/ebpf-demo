# container_execsnoop_ppid

## compile

```shell
$ make libbpf
$ make vmliunx
$ make 
$ ./container_execsnoop_ppid
NETNS        UTSNS        CONTAINER    COMMAND PID    PPID   RET ARGS
4026531840   4026531838   ubuntu       setsid 246351 213432 0  /usr/bin/setsid /usr/bin/git -c credential.helper= -c core.quotepath=false -c log.showSignature=false status --porcelain -z --no-renames --untracked-files=all --ignored=matching -- eBPF-C/container_execsnoop_ppid/container_execsnoop_ppid.bpf.o eBPF-C/container_execsnoop_ppid/container_execsnoop_ppid eBPF-C/container_execsnoop_ppid/container_execsnoop_ppid.o 
4026531840   4026531838   ubuntu       git    246351 213432 0  /usr/bin/git -c credential.helper= -c core.quotepath=false -c log.showSignature=false status --porcelain -z --no-renames --untracked-files=all --ignored=matching -- eBPF-C/container_execsnoop_ppid/container_execsnoop_ppid.bpf.o eBPF-C/container_execsnoop_ppid/container_execsnoop_ppid eBPF-C/container_execsnoop_ppid/container_execsnoop_ppid.o 

```

## 原理分析

该程序通过静态跟踪的方式在sys_enter_execve、sys_exit_execve系统调用时获取当前执行进程所在的容器网络命名空间ID、容器ID、容器名称、执行命令、pid、ppid、返回值和参数,并将获取到的进程信息通过perf event映射的方式实时发送到用户空间；
其中入口函数和出口函数的数据共享通过execs映射实现;

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
