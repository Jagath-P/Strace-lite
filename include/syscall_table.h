#ifndef SYSCALL_TABLE_H
#define SYSCALL_TABLE_H

typedef enum { ARG_INT = 1, ARG_STR, ARG_HEX, ARG_FD } argtype_t;

struct syscall_def {
  long nr;
  const char *name;
  int nargs;
  argtype_t argtypes[6];
};

extern struct syscall_def table[];
extern const int table_size;

const struct syscall_def *find_syscall(long nr);

#endif
