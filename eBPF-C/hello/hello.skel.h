/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */

/* THIS FILE IS AUTOGENERATED BY BPFTOOL! */
#ifndef __HELLO_BPF_SKEL_H__
#define __HELLO_BPF_SKEL_H__

#include <errno.h>
#include <stdlib.h>
#include <bpf/libbpf.h>

struct hello_bpf {
	struct bpf_object_skeleton *skeleton;
	struct bpf_object *obj;
	struct {
		struct bpf_map *rodata;
	} maps;
	struct {
		struct bpf_program *tracepoint__syscalls__sys_enter_execve;
		struct bpf_program *tracepoint__syscalls__sys_exit_execve;
	} progs;
	struct {
		struct bpf_link *tracepoint__syscalls__sys_enter_execve;
		struct bpf_link *tracepoint__syscalls__sys_exit_execve;
	} links;
	struct hello_bpf__rodata {
	} *rodata;

#ifdef __cplusplus
	static inline struct hello_bpf *open(const struct bpf_object_open_opts *opts = nullptr);
	static inline struct hello_bpf *open_and_load();
	static inline int load(struct hello_bpf *skel);
	static inline int attach(struct hello_bpf *skel);
	static inline void detach(struct hello_bpf *skel);
	static inline void destroy(struct hello_bpf *skel);
	static inline const void *elf_bytes(size_t *sz);
#endif /* __cplusplus */
};

static void
hello_bpf__destroy(struct hello_bpf *obj)
{
	if (!obj)
		return;
	if (obj->skeleton)
		bpf_object__destroy_skeleton(obj->skeleton);
	free(obj);
}

static inline int
hello_bpf__create_skeleton(struct hello_bpf *obj);

static inline struct hello_bpf *
hello_bpf__open_opts(const struct bpf_object_open_opts *opts)
{
	struct hello_bpf *obj;
	int err;

	obj = (struct hello_bpf *)calloc(1, sizeof(*obj));
	if (!obj) {
		errno = ENOMEM;
		return NULL;
	}

	err = hello_bpf__create_skeleton(obj);
	if (err)
		goto err_out;

	err = bpf_object__open_skeleton(obj->skeleton, opts);
	if (err)
		goto err_out;

	return obj;
err_out:
	hello_bpf__destroy(obj);
	errno = -err;
	return NULL;
}

static inline struct hello_bpf *
hello_bpf__open(void)
{
	return hello_bpf__open_opts(NULL);
}

static inline int
hello_bpf__load(struct hello_bpf *obj)
{
	return bpf_object__load_skeleton(obj->skeleton);
}

static inline struct hello_bpf *
hello_bpf__open_and_load(void)
{
	struct hello_bpf *obj;
	int err;

	obj = hello_bpf__open();
	if (!obj)
		return NULL;
	err = hello_bpf__load(obj);
	if (err) {
		hello_bpf__destroy(obj);
		errno = -err;
		return NULL;
	}
	return obj;
}

static inline int
hello_bpf__attach(struct hello_bpf *obj)
{
	return bpf_object__attach_skeleton(obj->skeleton);
}

static inline void
hello_bpf__detach(struct hello_bpf *obj)
{
	return bpf_object__detach_skeleton(obj->skeleton);
}

static inline const void *hello_bpf__elf_bytes(size_t *sz);

static inline int
hello_bpf__create_skeleton(struct hello_bpf *obj)
{
	struct bpf_object_skeleton *s;
	int err;

	s = (struct bpf_object_skeleton *)calloc(1, sizeof(*s));
	if (!s)	{
		err = -ENOMEM;
		goto err;
	}

	s->sz = sizeof(*s);
	s->name = "hello_bpf";
	s->obj = &obj->obj;

	/* maps */
	s->map_cnt = 1;
	s->map_skel_sz = sizeof(*s->maps);
	s->maps = (struct bpf_map_skeleton *)calloc(s->map_cnt, s->map_skel_sz);
	if (!s->maps) {
		err = -ENOMEM;
		goto err;
	}

	s->maps[0].name = "hello_bp.rodata";
	s->maps[0].map = &obj->maps.rodata;
	s->maps[0].mmaped = (void **)&obj->rodata;

	/* programs */
	s->prog_cnt = 2;
	s->prog_skel_sz = sizeof(*s->progs);
	s->progs = (struct bpf_prog_skeleton *)calloc(s->prog_cnt, s->prog_skel_sz);
	if (!s->progs) {
		err = -ENOMEM;
		goto err;
	}

	s->progs[0].name = "tracepoint__syscalls__sys_enter_execve";
	s->progs[0].prog = &obj->progs.tracepoint__syscalls__sys_enter_execve;
	s->progs[0].link = &obj->links.tracepoint__syscalls__sys_enter_execve;

	s->progs[1].name = "tracepoint__syscalls__sys_exit_execve";
	s->progs[1].prog = &obj->progs.tracepoint__syscalls__sys_exit_execve;
	s->progs[1].link = &obj->links.tracepoint__syscalls__sys_exit_execve;

	s->data = (void *)hello_bpf__elf_bytes(&s->data_sz);

	obj->skeleton = s;
	return 0;
err:
	bpf_object__destroy_skeleton(s);
	return err;
}

static inline const void *hello_bpf__elf_bytes(size_t *sz)
{
	*sz = 8888;
	return (const void *)"\
\x7f\x45\x4c\x46\x02\x01\x01\0\0\0\0\0\0\0\0\0\x01\0\xf7\0\x01\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\xf8\x1b\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\x40\0\x1b\0\
\x01\0\x79\x16\x10\0\0\0\0\0\x85\0\0\0\x0e\0\0\0\x18\x01\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\xb7\x02\0\0\x11\0\0\0\xbf\x03\0\0\0\0\0\0\xbf\x64\0\0\0\0\0\0\x85\0\0\0\
\x06\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\0\0\0\0\0\0\xbf\x16\0\0\0\0\0\0\x85\0\0\0\
\x0e\0\0\0\x79\x64\x10\0\0\0\0\0\x18\x01\0\0\x11\0\0\0\0\0\0\0\0\0\0\0\xb7\x02\
\0\0\x19\0\0\0\xbf\x03\0\0\0\0\0\0\x85\0\0\0\x06\0\0\0\xb7\0\0\0\0\0\0\0\x95\0\
\0\0\0\0\0\0\x44\x75\x61\x6c\x20\x42\x53\x44\x2f\x47\x50\x4c\0\x50\x72\x6f\x63\
\x65\x73\x73\x5b\x25\x64\x5d\x3a\x20\x25\x73\x0a\0\x50\x72\x6f\x63\x65\x73\x73\
\x5b\x25\x64\x5d\x3a\x20\x72\x65\x74\x75\x72\x6e\x3a\x20\x25\x64\x0a\0\x63\x6c\
\x61\x6e\x67\x20\x76\x65\x72\x73\x69\x6f\x6e\x20\x31\x30\x2e\x30\x2e\x30\x2d\
\x34\x75\x62\x75\x6e\x74\x75\x31\x20\0\x68\x65\x6c\x6c\x6f\x2e\x62\x70\x66\x2e\
\x63\0\x2f\x68\x6f\x6d\x65\x2f\x79\x75\x61\x6e\x73\x68\x65\x6e\x67\x72\x6f\x6e\
\x67\x2f\x77\x6f\x72\x6b\x73\x70\x61\x63\x65\x2f\x65\x62\x70\x66\x2d\x64\x65\
\x6d\x6f\x2f\x65\x42\x50\x46\x2d\x43\x2f\x68\x65\x6c\x6c\x6f\0\x4c\x49\x43\x45\
\x4e\x53\x45\0\x63\x68\x61\x72\0\x5f\x5f\x41\x52\x52\x41\x59\x5f\x53\x49\x5a\
\x45\x5f\x54\x59\x50\x45\x5f\x5f\0\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x62\x70\x66\
\x5f\x67\x65\x74\x5f\x63\x75\x72\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\
\x69\x64\0\x6c\x6f\x6e\x67\x20\x6c\x6f\x6e\x67\x20\x75\x6e\x73\x69\x67\x6e\x65\
\x64\x20\x69\x6e\x74\0\x5f\x5f\x75\x36\x34\0\x62\x70\x66\x5f\x74\x72\x61\x63\
\x65\x5f\x70\x72\x69\x6e\x74\x6b\0\x6c\x6f\x6e\x67\x20\x69\x6e\x74\0\x75\x6e\
\x73\x69\x67\x6e\x65\x64\x20\x69\x6e\x74\0\x5f\x5f\x75\x33\x32\0\x6c\x6f\x6e\
\x67\x20\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x69\x6e\x74\0\x74\x72\x61\x63\x65\
\x70\x6f\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\
\x73\x5f\x65\x6e\x74\x65\x72\x5f\x65\x78\x65\x63\x76\x65\0\x69\x6e\x74\0\x74\
\x72\x61\x63\x65\x70\x6f\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\
\x5f\x5f\x73\x79\x73\x5f\x65\x78\x69\x74\x5f\x65\x78\x65\x63\x76\x65\0\x63\x74\
\x78\0\x65\x6e\x74\0\x74\x79\x70\x65\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x73\
\x68\x6f\x72\x74\0\x66\x6c\x61\x67\x73\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\
\x63\x68\x61\x72\0\x70\x72\x65\x65\x6d\x70\x74\x5f\x63\x6f\x75\x6e\x74\0\x70\
\x69\x64\0\x74\x72\x61\x63\x65\x5f\x65\x6e\x74\x72\x79\0\x69\x64\0\x61\x72\x67\
\x73\0\x5f\x5f\x64\x61\x74\x61\0\x74\x72\x61\x63\x65\x5f\x65\x76\x65\x6e\x74\
\x5f\x72\x61\x77\x5f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\0\x66\x69\x6c\x65\x6e\
\x61\x6d\x65\0\x5f\x5f\x6b\x65\x72\x6e\x65\x6c\x5f\x70\x69\x64\x5f\x74\0\x70\
\x69\x64\x5f\x74\0\x72\x65\x74\0\x74\x72\x61\x63\x65\x5f\x65\x76\x65\x6e\x74\
\x5f\x72\x61\x77\x5f\x73\x79\x73\x5f\x65\x78\x69\x74\0\xff\xff\xff\xff\xff\xff\
\xff\xff\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x01\0\x51\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\xff\xff\xff\xff\xff\xff\xff\xff\0\0\0\0\0\0\0\0\x08\0\0\
\0\0\0\0\0\x50\0\0\0\0\0\0\0\x01\0\x56\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xff\xff\
\xff\xff\xff\xff\xff\xff\0\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\
\x01\0\x50\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xff\xff\xff\xff\xff\xff\xff\xff\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\x01\0\x51\x08\0\0\0\0\0\0\0\x50\
\0\0\0\0\0\0\0\x01\0\x56\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xff\xff\xff\xff\xff\
\xff\xff\xff\0\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\x01\0\x50\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\x11\x01\x25\x0e\x13\x05\x03\x0e\x10\x17\x1b\
\x0e\x11\x01\x55\x17\0\0\x02\x34\0\x03\x0e\x49\x13\x3f\x19\x3a\x0b\x3b\x0b\x02\
\x18\0\0\x03\x01\x01\x49\x13\0\0\x04\x21\0\x49\x13\x37\x0b\0\0\x05\x24\0\x03\
\x0e\x3e\x0b\x0b\x0b\0\0\x06\x24\0\x03\x0e\x0b\x0b\x3e\x0b\0\0\x07\x2e\x01\x11\
\x01\x12\x06\x40\x18\x97\x42\x19\x03\x0e\x3a\x0b\x3b\x0b\x27\x19\x49\x13\x3f\
\x19\0\0\x08\x34\0\x03\x0e\x49\x13\x3a\x0b\x3b\x0b\x02\x18\0\0\x09\x05\0\x02\
\x17\x03\x0e\x3a\x0b\x3b\x0b\x49\x13\0\0\x0a\x34\0\x02\x17\x03\x0e\x3a\x0b\x3b\
\x0b\x49\x13\0\0\x0b\x26\0\x49\x13\0\0\x0c\x34\0\x03\x0e\x49\x13\x3a\x0b\x3b\
\x05\0\0\x0d\x0f\0\x49\x13\0\0\x0e\x15\0\x49\x13\x27\x19\0\0\x0f\x16\0\x49\x13\
\x03\x0e\x3a\x0b\x3b\x0b\0\0\x10\x34\0\x03\x0e\x49\x13\x3a\x0b\x3b\x0b\0\0\x11\
\x15\x01\x49\x13\x27\x19\0\0\x12\x05\0\x49\x13\0\0\x13\x18\0\0\0\x14\x13\x01\
\x03\x0e\x0b\x0b\x3a\x0b\x3b\x05\0\0\x15\x0d\0\x03\x0e\x49\x13\x3a\x0b\x3b\x05\
\x38\x0b\0\0\0\x91\x02\0\0\x04\0\0\0\0\0\x08\x01\0\0\0\0\x0c\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x02\0\0\0\0\x3f\0\0\0\x01\x06\x09\x03\0\0\0\0\
\0\0\0\0\x03\x4b\0\0\0\x04\x52\0\0\0\x0d\0\x05\0\0\0\0\x06\x01\x06\0\0\0\0\x08\
\x07\x07\0\0\0\0\0\0\0\0\x50\0\0\0\x01\x5a\0\0\0\0\x01\x09\x99\x01\0\0\x08\0\0\
\0\0\xb5\0\0\0\x01\x0e\x09\x03\0\0\0\0\0\0\0\0\x09\0\0\0\0\0\0\0\0\x01\x09\xa0\
\x01\0\0\x0a\x33\0\0\0\0\0\0\0\x01\x0b\x6f\x01\0\0\x0a\x66\0\0\0\0\0\0\0\x01\
\x0c\x3b\x02\0\0\0\x03\xc1\0\0\0\x04\x52\0\0\0\x11\0\x0b\x4b\0\0\0\x07\0\0\0\0\
\0\0\0\0\x50\0\0\0\x01\x5a\0\0\0\0\x01\x13\x99\x01\0\0\x08\0\0\0\0\x13\x01\0\0\
\x01\x17\x09\x03\x11\0\0\0\0\0\0\0\x09\x99\0\0\0\0\0\0\0\x01\x13\x51\x02\0\0\
\x0a\xdf\0\0\0\0\0\0\0\x01\x15\x3b\x02\0\0\0\x03\xc1\0\0\0\x04\x52\0\0\0\x19\0\
\x0c\0\0\0\0\x2b\x01\0\0\x03\x6f\x01\x0d\x30\x01\0\0\x0e\x35\x01\0\0\x0f\x40\
\x01\0\0\0\0\0\0\x02\x16\x05\0\0\0\0\x07\x08\x10\0\0\0\0\x52\x01\0\0\x03\xb0\
\x0d\x57\x01\0\0\x11\x68\x01\0\0\x12\x6f\x01\0\0\x12\x74\x01\0\0\x13\0\x05\0\0\
\0\0\x05\x08\x0d\xc1\0\0\0\x0f\x7f\x01\0\0\0\0\0\0\x02\x12\x05\0\0\0\0\x07\x04\
\x03\x92\x01\0\0\x04\x52\0\0\0\x06\0\x05\0\0\0\0\x07\x08\x05\0\0\0\0\x05\x04\
\x0d\xa5\x01\0\0\x14\0\0\0\0\x40\x02\x77\x8e\x15\0\0\0\0\xe3\x01\0\0\x02\x78\
\x8e\0\x15\0\0\0\0\x68\x01\0\0\x02\x79\x8e\x08\x15\0\0\0\0\x86\x01\0\0\x02\x7a\
\x8e\x10\x15\0\0\0\0\x2f\x02\0\0\x02\x7b\x8e\x40\0\x14\0\0\0\0\x08\x02\xba\x2e\
\x15\0\0\0\0\x21\x02\0\0\x02\xbb\x2e\0\x15\0\0\0\0\x28\x02\0\0\x02\xbc\x2e\x02\
\x15\0\0\0\0\x28\x02\0\0\x02\xbd\x2e\x03\x15\0\0\0\0\x99\x01\0\0\x02\xbe\x2e\
\x04\0\x05\0\0\0\0\x07\x02\x05\0\0\0\0\x08\x01\x03\x4b\0\0\0\x04\x52\0\0\0\0\0\
\x0f\x46\x02\0\0\0\0\0\0\x02\x4d\x0f\x99\x01\0\0\0\0\0\0\x02\x31\x0d\x56\x02\0\
\0\x14\0\0\0\0\x18\x02\x7e\x8e\x15\0\0\0\0\xe3\x01\0\0\x02\x7f\x8e\0\x15\0\0\0\
\0\x68\x01\0\0\x02\x80\x8e\x08\x15\0\0\0\0\x68\x01\0\0\x02\x81\x8e\x10\x15\0\0\
\0\0\x2f\x02\0\0\x02\x82\x8e\x18\0\0\0\0\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x50\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9f\xeb\x01\0\x18\0\
\0\0\0\0\0\0\x6c\x02\0\0\x6c\x02\0\0\x7c\x03\0\0\0\0\0\0\0\0\0\x02\x02\0\0\0\
\x01\0\0\0\x04\0\0\x04\x40\0\0\0\x1b\0\0\0\x03\0\0\0\0\0\0\0\x1f\0\0\0\x07\0\0\
\0\x40\0\0\0\x22\0\0\0\x09\0\0\0\x80\0\0\0\x27\0\0\0\x0c\0\0\0\0\x02\0\0\x2e\0\
\0\0\x04\0\0\x04\x08\0\0\0\x3a\0\0\0\x04\0\0\0\0\0\0\0\x3f\0\0\0\x05\0\0\0\x10\
\0\0\0\x45\0\0\0\x05\0\0\0\x18\0\0\0\x53\0\0\0\x06\0\0\0\x20\0\0\0\x57\0\0\0\0\
\0\0\x01\x02\0\0\0\x10\0\0\0\x66\0\0\0\0\0\0\x01\x01\0\0\0\x08\0\0\0\x74\0\0\0\
\0\0\0\x01\x04\0\0\0\x20\0\0\x01\x78\0\0\0\0\0\0\x01\x08\0\0\0\x40\0\0\x01\x81\
\0\0\0\0\0\0\x01\x08\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x08\0\0\0\x0a\0\
\0\0\x06\0\0\0\x93\0\0\0\0\0\0\x01\x04\0\0\0\x20\0\0\0\xa7\0\0\0\0\0\0\x01\x01\
\0\0\0\x08\0\0\x01\0\0\0\0\0\0\0\x03\0\0\0\0\x0b\0\0\0\x0a\0\0\0\0\0\0\0\0\0\0\
\0\x01\0\0\x0d\x06\0\0\0\xac\0\0\0\x01\0\0\0\xb0\0\0\0\x01\0\0\x0c\x0d\0\0\0\0\
\0\0\0\0\0\0\x02\x10\0\0\0\xd6\x01\0\0\x04\0\0\x04\x18\0\0\0\x1b\0\0\0\x03\0\0\
\0\0\0\0\0\x1f\0\0\0\x07\0\0\0\x40\0\0\0\xef\x01\0\0\x07\0\0\0\x80\0\0\0\x27\0\
\0\0\x0c\0\0\0\xc0\0\0\0\0\0\0\0\x01\0\0\x0d\x06\0\0\0\xac\0\0\0\x0f\0\0\0\xf3\
\x01\0\0\x01\0\0\x0c\x11\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x0b\0\0\0\x0a\0\0\0\
\x0d\0\0\0\x07\x03\0\0\0\0\0\x0e\x13\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\x0a\x0b\0\0\
\0\0\0\0\0\0\0\0\x03\0\0\0\0\x15\0\0\0\x0a\0\0\0\x11\0\0\0\x0f\x03\0\0\0\0\0\
\x0e\x16\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\0\0\0\x15\0\0\0\x0a\0\0\0\x19\0\0\0\
\x3e\x03\0\0\0\0\0\x0e\x18\0\0\0\0\0\0\0\x6c\x03\0\0\x02\0\0\x0f\0\0\0\0\x17\0\
\0\0\0\0\0\0\x11\0\0\0\x19\0\0\0\x11\0\0\0\x19\0\0\0\x74\x03\0\0\x01\0\0\x0f\0\
\0\0\0\x14\0\0\0\0\0\0\0\x0d\0\0\0\0\x74\x72\x61\x63\x65\x5f\x65\x76\x65\x6e\
\x74\x5f\x72\x61\x77\x5f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\0\x65\x6e\x74\0\
\x69\x64\0\x61\x72\x67\x73\0\x5f\x5f\x64\x61\x74\x61\0\x74\x72\x61\x63\x65\x5f\
\x65\x6e\x74\x72\x79\0\x74\x79\x70\x65\0\x66\x6c\x61\x67\x73\0\x70\x72\x65\x65\
\x6d\x70\x74\x5f\x63\x6f\x75\x6e\x74\0\x70\x69\x64\0\x75\x6e\x73\x69\x67\x6e\
\x65\x64\x20\x73\x68\x6f\x72\x74\0\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x63\x68\
\x61\x72\0\x69\x6e\x74\0\x6c\x6f\x6e\x67\x20\x69\x6e\x74\0\x6c\x6f\x6e\x67\x20\
\x75\x6e\x73\x69\x67\x6e\x65\x64\x20\x69\x6e\x74\0\x5f\x5f\x41\x52\x52\x41\x59\
\x5f\x53\x49\x5a\x45\x5f\x54\x59\x50\x45\x5f\x5f\0\x63\x68\x61\x72\0\x63\x74\
\x78\0\x74\x72\x61\x63\x65\x70\x6f\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\
\x6c\x73\x5f\x5f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\x5f\x65\x78\x65\x63\x76\
\x65\0\x74\x70\x2f\x73\x79\x73\x63\x61\x6c\x6c\x73\x2f\x73\x79\x73\x5f\x65\x6e\
\x74\x65\x72\x5f\x65\x78\x65\x63\x76\x65\0\x30\x3a\x32\x3a\x30\0\x2f\x68\x6f\
\x6d\x65\x2f\x79\x75\x61\x6e\x73\x68\x65\x6e\x67\x72\x6f\x6e\x67\x2f\x77\x6f\
\x72\x6b\x73\x70\x61\x63\x65\x2f\x65\x62\x70\x66\x2d\x64\x65\x6d\x6f\x2f\x65\
\x42\x50\x46\x2d\x43\x2f\x68\x65\x6c\x6c\x6f\x2f\x68\x65\x6c\x6c\x6f\x2e\x62\
\x70\x66\x2e\x63\0\x09\x63\x6f\x6e\x73\x74\x20\x63\x68\x61\x72\x20\x2a\x66\x69\
\x6c\x65\x6e\x61\x6d\x65\x20\x3d\x20\x28\x63\x6f\x6e\x73\x74\x20\x63\x68\x61\
\x72\x20\x2a\x29\x28\x63\x74\x78\x2d\x3e\x61\x72\x67\x73\x5b\x30\x5d\x29\x3b\0\
\x09\x70\x69\x64\x5f\x74\x20\x70\x69\x64\x20\x3d\x20\x62\x70\x66\x5f\x67\x65\
\x74\x5f\x63\x75\x72\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\x69\x64\x28\
\x29\x3b\0\x09\x62\x70\x66\x5f\x70\x72\x69\x6e\x74\x6b\x28\x22\x50\x72\x6f\x63\
\x65\x73\x73\x5b\x25\x64\x5d\x3a\x20\x25\x73\x5c\x6e\x22\x2c\x20\x70\x69\x64\
\x2c\x20\x66\x69\x6c\x65\x6e\x61\x6d\x65\x29\x3b\0\x09\x72\x65\x74\x75\x72\x6e\
\x20\x30\x3b\0\x74\x72\x61\x63\x65\x5f\x65\x76\x65\x6e\x74\x5f\x72\x61\x77\x5f\
\x73\x79\x73\x5f\x65\x78\x69\x74\0\x72\x65\x74\0\x74\x72\x61\x63\x65\x70\x6f\
\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\
\x65\x78\x69\x74\x5f\x65\x78\x65\x63\x76\x65\0\x74\x72\x61\x63\x65\x70\x6f\x69\
\x6e\x74\x2f\x73\x79\x73\x63\x61\x6c\x6c\x73\x2f\x73\x79\x73\x5f\x65\x78\x69\
\x74\x5f\x65\x78\x65\x63\x76\x65\0\x69\x6e\x74\x20\x74\x72\x61\x63\x65\x70\x6f\
\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\
\x65\x78\x69\x74\x5f\x65\x78\x65\x63\x76\x65\x28\x73\x74\x72\x75\x63\x74\x20\
\x74\x72\x61\x63\x65\x5f\x65\x76\x65\x6e\x74\x5f\x72\x61\x77\x5f\x73\x79\x73\
\x5f\x65\x78\x69\x74\x20\x2a\x63\x74\x78\x29\0\x20\x20\x20\x20\x70\x69\x64\x5f\
\x74\x20\x70\x69\x64\x20\x3d\x20\x62\x70\x66\x5f\x67\x65\x74\x5f\x63\x75\x72\
\x72\x65\x6e\x74\x5f\x70\x69\x64\x5f\x74\x67\x69\x64\x28\x29\x3b\0\x30\x3a\x32\
\0\x20\x20\x20\x20\x62\x70\x66\x5f\x70\x72\x69\x6e\x74\x6b\x28\x22\x50\x72\x6f\
\x63\x65\x73\x73\x5b\x25\x64\x5d\x3a\x20\x72\x65\x74\x75\x72\x6e\x3a\x20\x25\
\x64\x5c\x6e\x22\x2c\x20\x70\x69\x64\x2c\x20\x63\x74\x78\x2d\x3e\x72\x65\x74\
\x29\x3b\0\x20\x20\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\0\x4c\x49\x43\
\x45\x4e\x53\x45\0\x74\x72\x61\x63\x65\x70\x6f\x69\x6e\x74\x5f\x5f\x73\x79\x73\
\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\x5f\x65\x78\
\x65\x63\x76\x65\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x74\x72\x61\x63\x65\x70\x6f\
\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\
\x65\x78\x69\x74\x5f\x65\x78\x65\x63\x76\x65\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\
\x2e\x72\x6f\x64\x61\x74\x61\0\x6c\x69\x63\x65\x6e\x73\x65\0\x9f\xeb\x01\0\x20\
\0\0\0\0\0\0\0\x24\0\0\0\x24\0\0\0\x94\0\0\0\xb8\0\0\0\x34\0\0\0\x08\0\0\0\xd7\
\0\0\0\x01\0\0\0\0\0\0\0\x0e\0\0\0\x19\x02\0\0\x01\0\0\0\0\0\0\0\x12\0\0\0\x10\
\0\0\0\xd7\0\0\0\x04\0\0\0\0\0\0\0\xfa\0\0\0\x3b\x01\0\0\x28\x2c\0\0\x08\0\0\0\
\xfa\0\0\0\x71\x01\0\0\x0e\x30\0\0\x10\0\0\0\xfa\0\0\0\x9a\x01\0\0\x02\x38\0\0\
\x40\0\0\0\xfa\0\0\0\xcb\x01\0\0\x02\x3c\0\0\x19\x02\0\0\x04\0\0\0\0\0\0\0\xfa\
\0\0\0\x3d\x02\0\0\0\x4c\0\0\x08\0\0\0\xfa\0\0\0\x8d\x02\0\0\x11\x54\0\0\x10\0\
\0\0\xfa\0\0\0\xbd\x02\0\0\x05\x5c\0\0\x40\0\0\0\xfa\0\0\0\xf9\x02\0\0\x05\x60\
\0\0\x10\0\0\0\xd7\0\0\0\x01\0\0\0\0\0\0\0\x02\0\0\0\xf4\0\0\0\0\0\0\0\x19\x02\
\0\0\x01\0\0\0\x10\0\0\0\x10\0\0\0\xb9\x02\0\0\0\0\0\0\0\0\0\0\x0c\0\0\0\xff\
\xff\xff\xff\x04\0\x08\0\x08\x7c\x0b\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x50\0\
\0\0\0\0\0\0\x14\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\xa0\0\0\0\x04\
\0\x61\0\0\0\x08\x01\x01\xfb\x0e\x0d\0\x01\x01\x01\x01\0\0\0\x01\0\0\x01\x2e\0\
\x2e\x2e\x2f\x6c\x69\x62\x62\x70\x66\x2f\x75\x73\x72\x2f\x69\x6e\x63\x6c\x75\
\x64\x65\x2f\x62\x70\x66\0\0\x68\x65\x6c\x6c\x6f\x2e\x62\x70\x66\x2e\x63\0\0\0\
\0\x76\x6d\x6c\x69\x6e\x75\x78\x2e\x68\0\x01\0\0\x62\x70\x66\x5f\x68\x65\x6c\
\x70\x65\x72\x5f\x64\x65\x66\x73\x2e\x68\0\x02\0\0\0\0\x09\x02\0\0\0\0\0\0\0\0\
\x03\x09\x01\x05\x28\x0a\x13\x05\x0e\x21\x05\x02\x22\x67\x02\x02\0\x01\x01\0\
\x09\x02\0\0\0\0\0\0\0\0\x03\x13\x01\x05\x11\x0a\x21\x05\x05\x22\x67\x02\x02\0\
\x01\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x88\x01\0\0\
\x04\0\xf1\xff\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x1f\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x09\0\x2b\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x60\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x68\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x09\0\x6d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x81\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x89\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x09\0\xa2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xb9\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xbf\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x09\0\xd0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xd9\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xe6\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x09\0\xec\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xfe\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x25\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x09\0\x29\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x4f\x01\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x53\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x09\0\x57\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x5c\
\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x6b\x01\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x09\0\x71\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\
\0\x7f\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x8d\x01\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\x91\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\x09\0\x9d\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xa0\x01\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xa5\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x09\0\xac\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xc6\x01\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xcf\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\x09\0\xde\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xe4\
\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x09\0\xe8\x01\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x50\0\0\0\x01\0\x08\0\0\0\0\0\0\0\0\0\x11\0\0\0\0\0\0\0\x22\0\0\0\x01\
\0\x08\0\x11\0\0\0\0\0\0\0\x19\0\0\0\0\0\0\0\0\0\0\0\x03\0\x03\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x05\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x03\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x0a\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x0c\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\x03\0\x0f\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x15\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x03\0\x17\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb5\x01\
\0\0\x11\0\x07\0\0\0\0\0\0\0\0\0\x0d\0\0\0\0\0\0\0\x08\x01\0\0\x12\0\x03\0\0\0\
\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\xba\0\0\0\x12\0\x05\0\0\0\0\0\0\0\0\0\x50\0\0\0\
\0\0\0\0\x10\0\0\0\0\0\0\0\x01\0\0\0\x2a\0\0\0\x18\0\0\0\0\0\0\0\x01\0\0\0\x2a\
\0\0\0\x08\0\0\0\0\0\0\0\x01\0\0\0\x28\0\0\0\x3b\0\0\0\0\0\0\0\x01\0\0\0\x28\0\
\0\0\x6e\0\0\0\0\0\0\0\x01\0\0\0\x28\0\0\0\xa1\0\0\0\0\0\0\0\x01\0\0\0\x29\0\0\
\0\xe7\0\0\0\0\0\0\0\x01\0\0\0\x29\0\0\0\x06\0\0\0\0\0\0\0\x0a\0\0\0\x2c\0\0\0\
\x0c\0\0\0\0\0\0\0\x0a\0\0\0\x02\0\0\0\x12\0\0\0\0\0\0\0\x0a\0\0\0\x03\0\0\0\
\x16\0\0\0\0\0\0\0\x0a\0\0\0\x2f\0\0\0\x1a\0\0\0\0\0\0\0\x0a\0\0\0\x04\0\0\0\
\x26\0\0\0\0\0\0\0\x0a\0\0\0\x2d\0\0\0\x2b\0\0\0\0\0\0\0\x0a\0\0\0\x05\0\0\0\
\x37\0\0\0\0\0\0\0\x01\0\0\0\x30\0\0\0\x4c\0\0\0\0\0\0\0\x0a\0\0\0\x06\0\0\0\
\x53\0\0\0\0\0\0\0\x0a\0\0\0\x07\0\0\0\x5a\0\0\0\0\0\0\0\x01\0\0\0\x28\0\0\0\
\x68\0\0\0\0\0\0\0\x0a\0\0\0\x11\0\0\0\x73\0\0\0\0\0\0\0\x0a\0\0\0\x08\0\0\0\
\x7f\0\0\0\0\0\0\0\x01\0\0\0\x2a\0\0\0\x88\0\0\0\0\0\0\0\x0a\0\0\0\x2b\0\0\0\
\x8c\0\0\0\0\0\0\0\x0a\0\0\0\x14\0\0\0\x97\0\0\0\0\0\0\0\x0a\0\0\0\x2b\0\0\0\
\x9b\0\0\0\0\0\0\0\x0a\0\0\0\x21\0\0\0\xa6\0\0\0\0\0\0\0\x0a\0\0\0\x2b\0\0\0\
\xaa\0\0\0\0\0\0\0\x0a\0\0\0\x1b\0\0\0\xc7\0\0\0\0\0\0\0\x01\0\0\0\x29\0\0\0\
\xd5\0\0\0\0\0\0\0\x0a\0\0\0\x13\0\0\0\xe0\0\0\0\0\0\0\0\x0a\0\0\0\x08\0\0\0\
\xec\0\0\0\0\0\0\0\x01\0\0\0\x2a\0\0\0\xf5\0\0\0\0\0\0\0\x0a\0\0\0\x2b\0\0\0\
\xf9\0\0\0\0\0\0\0\x0a\0\0\0\x14\0\0\0\x04\x01\0\0\0\0\0\0\x0a\0\0\0\x2b\0\0\0\
\x08\x01\0\0\0\0\0\0\x0a\0\0\0\x1b\0\0\0\x20\x01\0\0\0\0\0\0\x0a\0\0\0\x09\0\0\
\0\x3a\x01\0\0\0\0\0\0\x0a\0\0\0\x0b\0\0\0\x41\x01\0\0\0\0\0\0\x0a\0\0\0\x0a\0\
\0\0\x48\x01\0\0\0\0\0\0\x0a\0\0\0\x0c\0\0\0\x69\x01\0\0\0\0\0\0\x0a\0\0\0\x0d\
\0\0\0\x79\x01\0\0\0\0\0\0\x0a\0\0\0\x0f\0\0\0\x80\x01\0\0\0\0\0\0\x0a\0\0\0\
\x0e\0\0\0\x93\x01\0\0\0\0\0\0\x0a\0\0\0\x10\0\0\0\x9a\x01\0\0\0\0\0\0\x0a\0\0\
\0\x12\0\0\0\xa6\x01\0\0\0\0\0\0\x0a\0\0\0\x20\0\0\0\xaf\x01\0\0\0\0\0\0\x0a\0\
\0\0\x15\0\0\0\xbc\x01\0\0\0\0\0\0\x0a\0\0\0\x1d\0\0\0\xc9\x01\0\0\0\0\0\0\x0a\
\0\0\0\x1e\0\0\0\xd6\x01\0\0\0\0\0\0\x0a\0\0\0\x1f\0\0\0\xe4\x01\0\0\0\0\0\0\
\x0a\0\0\0\x1c\0\0\0\xed\x01\0\0\0\0\0\0\x0a\0\0\0\x16\0\0\0\xfa\x01\0\0\0\0\0\
\0\x0a\0\0\0\x18\0\0\0\x07\x02\0\0\0\0\0\0\x0a\0\0\0\x1a\0\0\0\x14\x02\0\0\0\0\
\0\0\x0a\0\0\0\x1b\0\0\0\x22\x02\0\0\0\0\0\0\x0a\0\0\0\x17\0\0\0\x29\x02\0\0\0\
\0\0\0\x0a\0\0\0\x19\0\0\0\x40\x02\0\0\0\0\0\0\x0a\0\0\0\x23\0\0\0\x4b\x02\0\0\
\0\0\0\0\x0a\0\0\0\x22\0\0\0\x57\x02\0\0\0\0\0\0\x0a\0\0\0\x25\0\0\0\x60\x02\0\
\0\0\0\0\0\x0a\0\0\0\x15\0\0\0\x6d\x02\0\0\0\0\0\0\x0a\0\0\0\x1d\0\0\0\x7a\x02\
\0\0\0\0\0\0\x0a\0\0\0\x24\0\0\0\x87\x02\0\0\0\0\0\0\x0a\0\0\0\x1f\0\0\0\0\0\0\
\0\0\0\0\0\x01\0\0\0\x28\0\0\0\x08\0\0\0\0\0\0\0\x01\0\0\0\x28\0\0\0\x10\0\0\0\
\0\0\0\0\x01\0\0\0\x29\0\0\0\x18\0\0\0\0\0\0\0\x01\0\0\0\x29\0\0\0\x58\x02\0\0\
\0\0\0\0\x0a\0\0\0\x2a\0\0\0\x64\x02\0\0\0\0\0\0\x0a\0\0\0\x2a\0\0\0\x7c\x02\0\
\0\0\0\0\0\0\0\0\0\x30\0\0\0\x2c\0\0\0\0\0\0\0\0\0\0\0\x28\0\0\0\x3c\0\0\0\0\0\
\0\0\0\0\0\0\x29\0\0\0\x50\0\0\0\0\0\0\0\0\0\0\0\x28\0\0\0\x60\0\0\0\0\0\0\0\0\
\0\0\0\x28\0\0\0\x70\0\0\0\0\0\0\0\0\0\0\0\x28\0\0\0\x80\0\0\0\0\0\0\0\0\0\0\0\
\x28\0\0\0\x98\0\0\0\0\0\0\0\0\0\0\0\x29\0\0\0\xa8\0\0\0\0\0\0\0\0\0\0\0\x29\0\
\0\0\xb8\0\0\0\0\0\0\0\0\0\0\0\x29\0\0\0\xc8\0\0\0\0\0\0\0\0\0\0\0\x29\0\0\0\
\xe4\0\0\0\0\0\0\0\0\0\0\0\x28\0\0\0\xfc\0\0\0\0\0\0\0\0\0\0\0\x29\0\0\0\x14\0\
\0\0\0\0\0\0\x0a\0\0\0\x2e\0\0\0\x18\0\0\0\0\0\0\0\x01\0\0\0\x28\0\0\0\x2c\0\0\
\0\0\0\0\0\x0a\0\0\0\x2e\0\0\0\x30\0\0\0\0\0\0\0\x01\0\0\0\x29\0\0\0\x6e\0\0\0\
\0\0\0\0\x01\0\0\0\x28\0\0\0\x8c\0\0\0\0\0\0\0\x01\0\0\0\x29\0\0\0\x31\x32\x30\
\x26\x27\0\x2e\x64\x65\x62\x75\x67\x5f\x61\x62\x62\x72\x65\x76\0\x2e\x74\x65\
\x78\x74\0\x2e\x72\x65\x6c\x2e\x42\x54\x46\x2e\x65\x78\x74\0\x74\x72\x61\x63\
\x65\x70\x6f\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\
\x79\x73\x5f\x65\x78\x69\x74\x5f\x65\x78\x65\x63\x76\x65\x2e\x5f\x5f\x5f\x5f\
\x66\x6d\x74\0\x74\x72\x61\x63\x65\x70\x6f\x69\x6e\x74\x5f\x5f\x73\x79\x73\x63\
\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\x5f\x65\x78\x65\
\x63\x76\x65\x2e\x5f\x5f\x5f\x5f\x66\x6d\x74\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\
\x75\x67\x5f\x72\x61\x6e\x67\x65\x73\0\x2e\x64\x65\x62\x75\x67\x5f\x73\x74\x72\
\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x69\x6e\x66\x6f\0\x2e\x6c\x6c\
\x76\x6d\x5f\x61\x64\x64\x72\x73\x69\x67\0\x74\x72\x61\x63\x65\x70\x6f\x69\x6e\
\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\x65\x78\
\x69\x74\x5f\x65\x78\x65\x63\x76\x65\0\x2e\x72\x65\x6c\x74\x72\x61\x63\x65\x70\
\x6f\x69\x6e\x74\x2f\x73\x79\x73\x63\x61\x6c\x6c\x73\x2f\x73\x79\x73\x5f\x65\
\x78\x69\x74\x5f\x65\x78\x65\x63\x76\x65\0\x74\x72\x61\x63\x65\x70\x6f\x69\x6e\
\x74\x5f\x5f\x73\x79\x73\x63\x61\x6c\x6c\x73\x5f\x5f\x73\x79\x73\x5f\x65\x6e\
\x74\x65\x72\x5f\x65\x78\x65\x63\x76\x65\0\x2e\x72\x65\x6c\x74\x70\x2f\x73\x79\
\x73\x63\x61\x6c\x6c\x73\x2f\x73\x79\x73\x5f\x65\x6e\x74\x65\x72\x5f\x65\x78\
\x65\x63\x76\x65\0\x6c\x69\x63\x65\x6e\x73\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\
\x62\x75\x67\x5f\x6c\x69\x6e\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\
\x66\x72\x61\x6d\x65\0\x2e\x72\x65\x6c\x2e\x64\x65\x62\x75\x67\x5f\x6c\x6f\x63\
\0\x68\x65\x6c\x6c\x6f\x2e\x62\x70\x66\x2e\x63\0\x2e\x73\x74\x72\x74\x61\x62\0\
\x2e\x73\x79\x6d\x74\x61\x62\0\x2e\x72\x6f\x64\x61\x74\x61\0\x2e\x72\x65\x6c\
\x2e\x42\x54\x46\0\x4c\x49\x43\x45\x4e\x53\x45\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x94\x01\0\0\x03\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x35\x1a\0\0\0\0\0\0\xbd\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\x0f\0\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x04\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\x33\x01\0\0\x01\0\0\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\
\x50\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x2f\x01\0\
\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xb0\x14\0\0\0\0\0\0\x10\0\0\0\0\0\
\0\0\x1a\0\0\0\x03\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xe4\0\0\0\x01\0\0\
\0\x06\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x90\0\0\0\0\0\0\0\x50\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xe0\0\0\0\x09\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\xc0\x14\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x1a\0\0\0\x05\0\0\0\
\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x50\x01\0\0\x01\0\0\0\x03\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\xe0\0\0\0\0\0\0\0\x0d\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\xa4\x01\0\0\x01\0\0\0\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\xed\0\0\0\0\0\0\0\x2a\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\x91\0\0\0\x01\0\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x17\x01\0\0\0\0\
\0\0\x01\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\
\x7d\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x18\x03\0\0\0\0\0\0\x12\
\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x79\x01\0\0\
\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xd0\x14\0\0\0\0\0\0\x50\0\0\0\0\0\0\
\0\x1a\0\0\0\x0a\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x01\0\0\0\x01\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x2a\x04\0\0\0\0\0\0\x01\x01\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xa0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\x2b\x05\0\0\0\0\0\0\x95\x02\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9c\0\0\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x20\x15\0\0\0\0\0\0\x80\x03\0\0\0\0\0\0\x1a\0\0\0\x0d\0\0\0\x08\0\0\0\0\0\
\0\0\x10\0\0\0\0\0\0\0\x83\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xc0\
\x07\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x7f\0\0\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xa0\x18\0\0\0\0\0\0\
\x40\0\0\0\0\0\0\0\x1a\0\0\0\x0f\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xb0\
\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xf0\x07\0\0\0\0\0\0\0\x06\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xac\x01\0\0\x09\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xe0\x18\0\0\0\0\0\0\x30\0\0\0\0\0\0\0\x1a\
\0\0\0\x11\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\x19\0\0\0\x01\0\0\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\xf0\x0d\0\0\0\0\0\0\x0c\x01\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x15\0\0\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x10\x19\0\0\0\0\0\0\xc0\0\0\0\0\0\0\0\x1a\0\0\0\x13\0\0\0\x08\0\0\
\0\0\0\0\0\x10\0\0\0\0\0\0\0\x6c\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\
\0\0\0\x0f\0\0\0\0\0\0\x40\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x08\0\0\0\0\0\0\0\0\0\
\0\0\0\0\0\0\x68\x01\0\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xd0\x19\0\0\
\0\0\0\0\x40\0\0\0\0\0\0\0\x1a\0\0\0\x15\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\
\0\0\x5c\x01\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x40\x0f\0\0\0\0\0\0\
\xa4\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x58\x01\0\
\0\x09\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x10\x1a\0\0\0\0\0\0\x20\0\0\0\0\0\
\0\0\x1a\0\0\0\x17\0\0\0\x08\0\0\0\0\0\0\0\x10\0\0\0\0\0\0\0\xac\0\0\0\x03\x4c\
\xff\x6f\0\0\0\x80\0\0\0\0\0\0\0\0\0\0\0\0\x30\x1a\0\0\0\0\0\0\x05\0\0\0\0\0\0\
\0\x1a\0\0\0\0\0\0\0\x01\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\x9c\x01\0\0\x02\0\0\0\0\
\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\xe8\x0f\0\0\0\0\0\0\xc8\x04\0\0\0\0\0\0\x01\0\0\
\0\x30\0\0\0\x08\0\0\0\0\0\0\0\x18\0\0\0\0\0\0\0";
}

#ifdef __cplusplus
struct hello_bpf *hello_bpf::open(const struct bpf_object_open_opts *opts) { return hello_bpf__open_opts(opts); }
struct hello_bpf *hello_bpf::open_and_load() { return hello_bpf__open_and_load(); }
int hello_bpf::load(struct hello_bpf *skel) { return hello_bpf__load(skel); }
int hello_bpf::attach(struct hello_bpf *skel) { return hello_bpf__attach(skel); }
void hello_bpf::detach(struct hello_bpf *skel) { hello_bpf__detach(skel); }
void hello_bpf::destroy(struct hello_bpf *skel) { hello_bpf__destroy(skel); }
const void *hello_bpf::elf_bytes(size_t *sz) { return hello_bpf__elf_bytes(sz); }
#endif /* __cplusplus */

__attribute__((unused)) static void
hello_bpf__assert(struct hello_bpf *s __attribute__((unused)))
{
#ifdef __cplusplus
#define _Static_assert static_assert
#endif
#ifdef __cplusplus
#undef _Static_assert
#endif
}

#endif /* __HELLO_BPF_SKEL_H__ */
