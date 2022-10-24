# bashreadline

## compile

```shell
$ make libbpf
$ make vmliunx
$ make 
$ ./bashreadline
TIME      PID     PPID    PATH             COMMAND
07:10:35  239133  213092  /usr/bin/bash    ls
07:10:38  239133  213092  /usr/bin/bash    top

```

## 原理分析

该程序通过用户态动态跟踪的方式在readline函数执行时获取当前bash执行的命令time,pid、ppid、path,并将获取到的进程信息通过perf event映射的方式实时发送到用户空间；

## 如何查询用户进程跟踪点？

在跟踪内核的状态之前，你需要利用内核提供的调试信息查询内核函数、内核跟踪点以及性能事件等。
类似地，在跟踪应用进程之前，你也需要知道这个进程所对应的二进制文件中提供了哪些可用的跟踪点。
那么，从哪里可以找到这些信息呢？如果你使用 GDB 之类的应用调试过程序，这时应该已经想到了，那就是应用程序二进制文件中的调试信息。
在静态语言的编译过程中，通常你可以加上  -g  选项保留调试信息。这样，源代码中的函数、变量以及它们对应的代码行号等信息，
就以  DWARF（Debugging With Attributed Record Formats，Linux 和类 Unix 平台最主流的调试信息格式）格式存储到了编译后的二进制文件中。
有了调试信息，你就可以通过  readelf、objdump、nm  等工具，查询可用于跟踪的函数、变量等符号列表。

```shell
# 查询符号表（RHEL8系统中请把动态库路径替换为/usr/lib64/libc.so.6）
readelf -Ws /usr/lib/x86_64-linux-gnu/libc.so.6

# 查询USDT信息（USDT信息位于ELF文件的notes段）
readelf -n /usr/lib/x86_64-linux-gnu/libc.so.6

# 查询uprobe（RHEL8系统中请把动态库路径替换为/usr/lib64/libc.so.6）
bpftrace -l 'uprobe:/usr/lib/x86_64-linux-gnu/libc.so.6:*'

# 查询USDT
bpftrace -l 'usdt:/usr/lib/x86_64-linux-gnu/libc.so.6:*'
```

同内核跟踪点类似，你也可以加上  -v  选项查询用户探针的参数格式。不过需要再次强调的是，
想要通过二进制文件查询符号表和参数定义，必须在编译的时候保留 DWARF 调试信息。
另外需要提醒你的是，uprobe 是基于文件的。当文件中的某个函数被跟踪时，除非对进程 PID 进行了过滤，默认所有使用到这个文件的进程都会被插桩。

以每个 Linux 用户都会使用的 Bash  为例（Bash 是一个典型的 C 语言程序）
```shell
# Ubuntu
sudo apt install bash-dbgsym

# RHEL
sudo debuginfo-install bash
```

有了 Bash 调试信息之后，再执行下面的几步，查询 Bash 的符号表：

```shell
# 第一步，查询 Build ID（用于关联调试信息）
readelf -n /usr/bin/bash | grep 'Build ID'
# 输出示例为：
#     Build ID: 7b140b33fd79d0861f831bae38a0cdfdf639d8bc

# 第二步，找到调试信息对应的文件（调试信息位于目录/usr/lib/debug/.build-id中，上一步中得到的Build ID前两个字母为目录名）
ls /usr/lib/debug/.build-id/7b/140b33fd79d0861f831bae38a0cdfdf639d8bc.debug

# 第三步，从调试信息中查询符号表
readelf -Ws /usr/lib/debug/.build-id/7b/140b33fd79d0861f831bae38a0cdfdf639d8bc.debug
```

参考 Bash 的源代码，每条 Bash 命令在运行前，都会调用  charreadline (const charprompt)  
函数读取用户的输入，然后再去解析执行（Bash 自身是使用编译型语言 C 开发的，而 Bash 语言则是一种解释型语言）。
注意，readline  函数的参数是命令行提示符（通过环境变量  PS1、PS2 等设置），而返回值才是用户的输入。
因而，我们只需要跟踪  readline  函数的返回值，也就是使用  uretprobe  跟踪。

