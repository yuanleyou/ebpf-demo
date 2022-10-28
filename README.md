# ebpf-demo

记录 ebpf 学习中的例子

* eBPF-BCC 使用BCC框架的学习实例
    * [bcc-prog](eBPF-BCC/bcc-prog/) - bcc 学习程序
        * [01-hello](eBPF-BCC/bcc-prog/01-hello) - 输出hello world的简单例子
        * [02-sys_sync](eBPF-BCC/bcc-prog/02-sys_sync) - kprobe动态跟踪sys_sync系统调用的例子
        * [03-hello_fields](eBPF-BCC/bcc-prog/03-hello_fields) - kprobe动态跟踪自定义系统调用的例子
        * [04-kprobe_tcp_v4_connect](eBPF-BCC/bcc-prog/04-kprobe_tcp_v4_connect) - kprobe动态跟踪TCP连接的例子
        * [05-tracepoint_probe](eBPF-BCC/bcc-prog/05-tracepoint_probe) - tracepoint静态跟踪random的例子
        * [06-system_call_tracepoint](eBPF-BCC/bcc-prog/06-system_call_tracepoint) - tracepoint静态跟踪系统调用的例子
        * [07-go_bash_readline](eBPF-BCC/bcc-prog/07-go_bash_readline) - 获取go程序参数的例子
        * [08-get_net_ns](eBPF-BCC/bcc-prog/08-get_net_ns) - 获取网络命名空间的例子
        * [09-trace_pkt](eBPF-BCC/bcc-prog/09-trace_pkt) - 动静结合跟踪网络包的例子
    * [Dockerfile](eBPF-BCC/Dockerfile) - 容器测试环境基础镜像Dockerfile文件
    * [run.sh](eBPF-BCC/run.sh) - 快速启动测试容器环境脚本
* eBPF-go 使用Cilium和Cloudflare维护的一个纯Go语言编写的库的学习实例

* eBPF-C 使用libbpf库的学习实例
    * [hello](eBPF-C/hello/) - 获取当前执行进程的pid和进程名称以及返回值的例子
    * [execsnoop](eBPF-C/execsnoop/) - 获取当前执行进程的pid,进程名称,进程执行参数以及返回值
    * [execsnoop_ppid](eBPF-C/execsnoop_ppid/) - 获取当前执行进程的pid,ppid,进程名称,进程执行参数以及返回值
    * [container_execsnoop_ppid](eBPF-C/container_execsnoop_ppid/) - 获取当前执行进程所在的容器网络命名空间ID、容器ID、容器名称、执行命令、pid、ppid、返回值和参数
    * [bashreadline](eBPF-C/bashreadline/) - 获取当前bash执行的命令time,pid、ppid、path
    * [xdp](eBPF-C/xdp/) - 获取网络包的大小
    * [traffic_controller](eBPF-C/traffic_controller/) - 将TCP目的端口为80的网络包丢弃
  
**在编译该目录下的项目时需要将[libbpf](https://github.com/libbpf/libbpf.git)源码拉取到eBPF-C同级目录才能编译**


## 跟踪点查询

### /proc/kallsyms

内核把所有函数以及非栈变量的地址都抽取到了 /proc/kallsyms 中，这样调试器就可以根据地址找出对应的函数和变量名称。很显然，具有实际含义的名称
要比 16 进制的地址易读得多。对内核插桩类的 eBPF 程序来说，它们要挂载的内核函数就可以从 /proc/kallsyms 这个文件中查到。注意，内核函数是一个
非稳定 API，在新版本中可能会发生变化，并且内核函数的数量也在不断增长中。以 v5.13.0 为例，总的内核符号表数量已经超过了 16 万。

```shell
$ cat /proc/kallsyms
```

不过需要提醒你的是，这些符号表不仅包含了内核函数，还包含了非栈数据变量。而且，并不是所有的内核函数都是可跟踪的，只有显式导出的内核函数才可以被
eBPF 进行动态跟踪。因而，通常我们并不直接从内核符号表查询可跟踪点，而是使用我接下来介绍的方法。

为了方便内核开发者获取所需的跟踪点信息，内核调试文件系统还向用户空间提供了内核调试所需的基本信息，如内核符号列表、跟踪点、函数跟踪（ftrace）状态
以及参数格式等。你可以在终端中执行 sudo ls /sys/kernel/debug 来查询内核调试文件系统的具体信息。比如，执行下面的命令，就可以查询 execve
系统调用的参数格式

```shell
sudo cat /sys/kernel/debug/tracing/events/syscalls/sys_enter_execve/format
```

如果你碰到了 /sys/kernel/debug 目录不存在的错误，说明你的系统没有自动挂载调试文件系统。只需要执行下面的 mount 命令就可以挂载它：

```shell
sudo mount -t debugfs debugfs /sys/kernel/debug
```

注意，eBPF 程序的执行也依赖于调试文件系统。如果你的系统没有自动挂载它，那么我推荐你把它加入到系统开机启动脚本里面，这样机器重启后 eBPF 程序也可以正常运行。

除了内核函数和跟踪点之外，性能事件又该如何查询呢？你可以使用 Linux 性能工具 perf 来查询性能事件的列表。如下面的命令所示，你可以不带参数查询所有的性能事件，也可以加入可选的事件类型参数进行过滤：

```shell
sudo perf list [hw|sw|cache|tracepoint|pmu|sdt|metric|metricgroup]
```

### bpftrace

bpftrace 是在 eBPF 和 BCC 之上构建了一个简化的跟踪语言，通过简单的几行脚本，就可以实现复杂的跟踪功能。并且，多行的跟踪指令也可以放到脚本文件中执行（脚本后缀通常为 .bt）

安装好 bpftrace 之后，你就可以执行 bpftrace -l 来查询内核插桩和跟踪点了。比如你可以通过以下几种方式来查询：

```shell
# 查询所有内核插桩和跟踪点
sudo bpftrace -l

# 使用通配符查询所有的系统调用跟踪点
sudo bpftrace -l 'tracepoint:syscalls:*'

# 使用通配符查询所有名字包含"execve"的跟踪点
sudo bpftrace -l '*execve*'
```

对于跟踪点来说，你还可以加上 -v 参数查询函数的入口参数或返回值。而由于内核函数属于不稳定的 API，在 bpftrace 中只能通过 arg0、arg1 这样的
参数来访问，具体的参数格式还需要参考内核源代码。

比如，下面就是一个查询系统调用 execve 入口参数（对应系统调用sys_enter_execve）和返回值（对应系统调用sys_exit_execve）的示例：

```shell
# 查询execve入口参数格式
$ sudo bpftrace -lv tracepoint:syscalls:sys_enter_execve
tracepoint:syscalls:sys_enter_execve
    int __syscall_nr
    const char * filename
    const char *const * argv
    const char *const * envp

# 查询execve返回值格式
$ sudo bpftrace -lv tracepoint:syscalls:sys_exit_execve
tracepoint:syscalls:sys_exit_execve
    int __syscall_nr
    long ret
```

所以，你既可以通过内核调试信息和 perf 来查询内核函数、跟踪点以及性能事件的列表，也可以使用 bpftrace 工具来查询。

## bpftrace 编程

由于 execve() 和 execveat() 这两个系统调用的入口参数文件名 filename 和命令行选项 argv ，以及返回值 ret 的定义都是一样的，因而我们可以把这两个跟踪点放到一起来处理。

首先，我们先忽略返回值，只看入口参数。打开一个终端，执行下面的 bpftrace 命令：

```shell
sudo bpftrace -e 'tracepoint:syscalls:sys_enter_execve,tracepoint:syscalls:sys_enter_execveat { printf("%-6d %-8s", pid, comm); join(args->argv);}'
```

这个命令中的具体内容含义如下：

* bpftrace -e 表示直接从后面的字符串参数中读入 bpftrace 程序（除此之外，它还支持从文件中读入 bpftrace 程序）；
* tracepoint:syscalls:sys_enter_execve,tracepoint:syscalls:sys_enter_execveat 表示用逗号分隔的多个跟踪点，其后的中括号表示跟踪点的处理函数；
* printf() 表示向终端中打印字符串，其用法类似于 C 语言中的 printf() 函数；
* pid 和 comm 是 bpftrace 内置的变量，分别表示进程 PID 和进程名称（你可以在其官方文档中找到其他的内置变量）；
* join(args->argv) 表示把字符串数组格式的参数用空格拼接起来，再打印到终端中。对于跟踪点来说，你可以使用 args->参数名 的方式直接读取参数（比如这里的 args->argv 就是读取系统调用中的 argv 参数）。

在另一个终端中执行 ls 命令，然后你会在第一个终端中看到如下的输出：

```shell
Attaching 2 probes...
157286 zsh     ls --color=tty
```

