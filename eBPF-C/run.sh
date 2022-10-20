#!/usr/bin/env bash

# docker build -t ubuntu20.04-ebpf-c:v1 .  # 构建测试环境基础镜像，第一次的时候运行

# shellcheck disable=SC2046
# shellcheck disable=SC2164
workdir=$(dirname $(pwd))

# mount -t debugfs debugfs /sys/kernel/debug

docker run -it --rm \
	--privileged \
	-v /sys/kernel/debug:/sys/kernel/debug:ro \
	--mount type=bind,source="$workdir",destination=/home/ebpf \
	--workdir /home/ebpf/eBPF-C \
	ubuntu20.04-ebpf-c:v1 bash