#!/usr/bin/python3

from bcc import BPF

BPF(src_file='sys_sync.c').trace_print()
