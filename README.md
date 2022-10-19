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
* eBPF-go 使用Cilium和Cloudflare维护的一个纯Go语言编写的库学习实例

