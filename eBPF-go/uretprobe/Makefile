APPS = uretprobe
GO := go
GO_BUILD = CGO_ENABLED=0 $(GO) build
GO_GENERATE = $(GO) generate
GO_TAGS ?=
CFLAGS := -O2 -g -Wall -Werror $(CFLAGS)

.PHONY: $(APPS)

$(APPS): export BPF_CFLAGS := $(CFLAGS)
$(APPS):
	$(GO_GENERATE)
	$(GO_BUILD) $(if $(GO_TAGS),-tags $(GO_TAGS))

clean:
	rm -f $(APPS)
	rm -f bpf_bpf*
