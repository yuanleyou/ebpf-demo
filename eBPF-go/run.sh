#!/usr/bin/env bash

# docker build -t ubuntu20.04-ebpf:v1 .  # 构建测试环境基础镜像，第一次的时候运行

# shellcheck disable=SC2046
# shellcheck disable=SC2164
workdir=$(cd $(dirname "$0"); pwd)

docker run -it --rm \
	--privileged \
	--env "GOPROXY=https://goproxy.cn" \
	--mount type=bind,source="$workdir",destination=/home/ebpf \
	--workdir /home/ebpf \
	ubuntu20.04-ebpf:v1 bash