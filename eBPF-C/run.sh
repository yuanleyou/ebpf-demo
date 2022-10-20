#!/usr/bin/env bash

# docker build -t ubuntu20.04-ebpf-C:v1 .  # 构建测试环境基础镜像，第一次的时候运行

# shellcheck disable=SC2046
# shellcheck disable=SC2164
workdir=$(cd $(dirname "$0"); pwd)

mount -t debugfs debugfs /sys/kernel/debug

docker run -it --rm \
	--privileged \
	--mount type=bind,source="$workdir",destination=/home/ebpf \
	--workdir /home/ebpf \
	ubuntu20.04-ebpf-C:v1 bash