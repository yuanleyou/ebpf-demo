#!/usr/bin/env bash

#docker build -t ubuntu20.04-ebpf:v1 .

docker run -it --rm \
	--privileged \
	--env "GOPROXY=https://goproxy.cn" \
	--mount type=bind,source=/home/ysr/ebpf-demo/eBPF-go,destination=/home/ebpf \
	--workdir /home/ebpf \
	ubuntu20.04-ebpf:v1 bash