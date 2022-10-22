
#ifndef __HELLO_H
#define __HELLO_H

#define ARGSIZE 128
#define TASK_COMM_LEN 16
#define TOTAL_MAX_ARGS 60
#define FULL_MAX_ARGS_ARR (TOTAL_MAX_ARGS * ARGSIZE)
#define BASE_EVENT_SIZE (size_t)(&((struct event*)0)->args)
#define EVENT_SIZE(e) (BASE_EVENT_SIZE + e->args_size)
#define LAST_ARG (FULL_MAX_ARGS_ARR - ARGSIZE)

struct event {
    char comm[TASK_COMM_LEN];
    pid_t pid;
    pid_t tgid;
    uid_t uid;
    pid_t ppid;
    int retval;
    int args_count;
    unsigned int args_size;
    char args[FULL_MAX_ARGS_ARR];
};

#endif