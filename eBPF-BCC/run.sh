#!/usr/bin/env bash

docker run -it --rm \
	--privileged \
	-v /lib/modules:/lib/modules:ro \
	-v /usr/src:/usr/src:ro \
	-v /etc/localtime:/etc/localtime:ro \
	-v /sys/kernel/debug:/sys/kernel/debug:ro \
	--mount type=bind,source=/home/ysr/ebpf-demo/eBPF-BCC/bcc-prog,destination=/usr/share/bcc/myspace \
	--workdir /usr/share/bcc \
	bcc-tools:v1 bash
