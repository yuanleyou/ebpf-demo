//go:build amd64

package main

import (
	"bytes"
	"encoding/binary"
	"errors"
	"github.com/cilium/ebpf/link"
	"github.com/cilium/ebpf/perf"
	"github.com/cilium/ebpf/rlimit"
	"golang.org/x/sys/unix"
	"log"
	"os"
	"os/signal"
	"syscall"
)

//go:generate sh -c "echo Generating for amd64"
//go:generate go run github.com/cilium/ebpf/cmd/bpf2go -cc clang bpf ./bpf/uretprobe.c -- -DOUTPUT_SKB -D__TARGET_ARCH_x86 -I./bpf/headers

const (
	binPath = "/bin/bash"
	symbol  = "readline"
)

type bpfEvent struct {
	Pid  uint32
	Line [80]uint8
}

func main() {
	stopper := make(chan os.Signal, 1)
	signal.Notify(stopper, os.Interrupt, syscall.SIGTERM)

	if err := rlimit.RemoveMemlock(); err != nil {
		log.Fatalln(err)
	}

	objs := bpfObjects{}
	if err := loadBpfObjects(&objs, nil); err != nil {
		log.Fatalf("loading objects: %v", err)
	}
	defer objs.Close()

	ex, err := link.OpenExecutable(binPath)
	if err != nil {
		log.Fatalf("opening uretprobe: %v", err)
	}

	up, err := ex.Uretprobe(symbol, objs.UretprobeBashReadline, nil)
	if err != nil {
		log.Fatalf("creating uretprobe: %v", err)
	}
	defer up.Close()

	rd, err := perf.NewReader(objs.Events, os.Getpagesize())
	if err != nil {
		log.Fatalf("creating perf event reader: %v", err)
	}
	defer rd.Close()

	go func() {
		<-stopper
		log.Println("Received signal, exiting program...")

		if err := rd.Close(); err != nil {
			log.Fatalf("closing perf event reader: %v", err)
		}
	}()

	log.Printf("Listening for events...")

	var event bpfEvent
	for {
		record, err := rd.Read()
		if err != nil {
			if errors.Is(err, perf.ErrClosed) {
				return
			}
			log.Printf("reading from perf event reader: %s", err)
			continue
		}

		if record.LostSamples != 0 {
			log.Printf("perf event ring buffer full, dropped %d samples", record.LostSamples)
			continue
		}

		if err := binary.Read(bytes.NewBuffer(record.RawSample), binary.LittleEndian, &event); err != nil {
			log.Printf("parsing perf event: %s", err)
			continue
		}

		log.Printf("%s:%s return value:%s", binPath, symbol, unix.ByteSliceToString(event.Line[:]))
	}
}
