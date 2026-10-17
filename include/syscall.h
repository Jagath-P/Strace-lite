#ifndef SYSCALL_TABLE_H
#define SYSCALL_TABLE_H
#include <stdlib.h>
typedef enum {
  ARG_INT = 1,
  ARG_STR,
  ARG_HEX,
  ARG_FD,
  ARG_FLAGS,
  ARG_OCT
} argtype_t;

struct syscall_def {
  long nr;
  const char *name;
  int nargs;
  int trace_bit;
  argtype_t argtypes[6];
};

extern struct syscall_def table[];
extern struct options Tropt;
extern const int table_size;

const struct syscall_def *find_syscall(long nr);
struct syscall_def *find_syscall_by_name(char *s);
void print_args(unsigned long long args[], int syscall_num, pid_t child);

#endif
