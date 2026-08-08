#ifndef SYSCALL_TABLE_H
#define SYSCALL_TABLE_H

typedef enum { ARG_INT = 1, ARG_STR, ARG_HEX, ARG_FD } argtype_t;

struct syscall_def {
  long nr;
  const char *name;
  int nargs;
  int trace_bit;
  argtype_t argtypes[6];
};

struct options {
  int e_flag;
  int f_flag;
};

extern struct syscall_def table[];
extern struct options Tropt;
extern const int table_size;

const struct syscall_def *find_syscall(long nr);
struct syscall_def *find_syscall_by_name(char *s);

#endif
