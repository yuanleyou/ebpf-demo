#!/usr/bin/env bash

# docker build -t bcc-tools:v1 .  # 构建测试环境基础镜像，第一次的时候运行

# shellcheck disable=SC2046
# shellcheck disable=SC2164
workdir=$(cd $(dirname "$0"); pwd)

docker run -it --rm \
	--privileged \
	-v /lib/modules:/lib/modules:ro \
	-v /usr/src:/usr/src:ro \
	-v /etc/localtime:/etc/localtime:ro \
	-v /sys/kernel/debug:/sys/kernel/debug:ro \
	--mount type=bind,source="$workdir",destination=/usr/share/bcc/myspace \
	--workdir /usr/share/bcc \
	bcc-tools:v1 bash
