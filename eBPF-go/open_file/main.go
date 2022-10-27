package main

import (
	"github.com/cilium/ebpf/link"
	"github.com/cilium/ebpf/rlimit"
	"log"
	"time"
)

const mapKey uint32 = 0

//go:generate sh -c "echo Generating for amd64"
//go:generate go run github.com/cilium/ebpf/cmd/bpf2go -cc clang bpf ./bpf/open_file.c -- -DOUTPUT_SKB -D__TARGET_ARCH_x86 -I./bpf/headers
func main() {

	// Name of the kernel function to trace.
	fn := "do_sys_openat2"

	// Allow the current process to lock memory for eBPF resources.
	if err := rlimit.RemoveMemlock(); err != nil {
		log.Fatal(err)
	}

	// Load pre-compiled programs and maps into the kernel.
	objs := bpfObjects{}
	if err := loadBpfObjects(&objs, nil); err != nil {
		log.Fatalf("loading objects: %v", err)
	}
	defer objs.Close()

	// Open a Kprobe at the entry point of the kernel function and attach the
	// pre-compiled program. Each time the kernel function enters, the program
	// will increment the execution counter by 1. The read loop below polls this
	// map value once per second.
	kp, err := link.Kprobe(fn, objs.KprobeDoSysOpenat2)
	if err != nil {
		log.Fatalf("opening kprobe: %s", err)
	}
	defer kp.Close()

	// Read loop reporting the total amount of times the kernel
	// function was entered, once per second.
	ticker := time.NewTicker(1 * time.Second)

	log.Println("Waiting for events..")

	for range ticker.C {
		var value uint64
		if err := objs.KprobeMap.Lookup(mapKey, &value); err != nil {
			log.Fatalf("reading map: %v", err)
		}
		log.Printf("%s called %d times\n", fn, value)
	}
}
