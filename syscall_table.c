#include "include/syscall.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct syscall_def table[] = {
    {257, "openat", 4, 0, {ARG_FD, ARG_STR, ARG_HEX, ARG_HEX}},
    {0, "read", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {1, "write", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {59, "execve", 3, 0, {ARG_STR, ARG_HEX, ARG_HEX}},
};

const int table_size = sizeof(table) / sizeof(table[0]);

const struct syscall_def *find_syscall(long nr) {
  for (int i = 0; i < table_size; i++) {
    if (table[i].nr == nr)
      return &table[i];
  }
  return NULL;
}

struct syscall_def *find_syscall_by_name(char *s) {
  for (int i = 0; i < table_size; i++) {
    if (!strcmp(table[i].name, s)) {
      return &table[i];
    }
  }

  return NULL;
}
