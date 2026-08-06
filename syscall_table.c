#include "include/syscall_table.h"
#include <stddef.h>

struct syscall_def table[] = {
    {257, "openat", 4, {ARG_FD, ARG_STR, ARG_HEX, ARG_HEX}},
    {0, "read", 3, {ARG_FD, ARG_HEX, ARG_INT}},
    {1, "write", 3, {ARG_FD, ARG_HEX, ARG_INT}},
    {2, "open", 3, {ARG_STR, ARG_HEX, ARG_HEX}},
    {59, "execve", 3, {ARG_STR, ARG_HEX, ARG_HEX}},
};

const int table_size = sizeof(table) / sizeof(table[0]);

const struct syscall_def *find_syscall(long nr) {
  for (int i = 0; i < table_size; i++) {
    if (table[i].nr == nr)
      return &table[i];
  }
  return NULL;
}
