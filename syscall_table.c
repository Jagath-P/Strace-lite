#include "include/api.h"
#include "include/syscall.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct syscall_def table[] = {
    {257, "openat", 4, 0, {ARG_FD, ARG_STR, ARG_FLAGS, ARG_OCT}},
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
void print_open_flags(unsigned long long v) {

  int acc = v & O_ACCMODE;
  if (acc == O_WRONLY)
    printf("O_WRONLY");
  else if (acc == O_RDWR)
    printf("O_RDWR");
  else
    printf("O_RDONLY");

  if (v & O_CREAT)
    printf("|O_CREAT");
  if (v & O_EXCL)
    printf("|O_EXCL");
  if (v & O_TRUNC)
    printf("|O_TRUNC");
  if (v & O_APPEND)
    printf("|O_APPEND");
  if (v & O_NONBLOCK)
    printf("|O_NONBLOCK");
  if (v & O_DIRECTORY)
    printf("|O_DIRECTORY");
  if (v & O_CLOEXEC)
    printf("|O_CLOEXEC");
}
void print_args(unsigned long long args[], int syscall_num, pid_t child) {
  const struct syscall_def *sc = find_syscall(syscall_num);
  if (!sc)
    return;
  for (int i = 0; i < sc->nargs; i++) {
    if (i == 0) {
      printf("syscall name: %s\n", sc->name);
    }
    if (sc->argtypes[i] == ARG_INT) {
      printf("arg %d: %lld", i + 1, args[i]);
    } else if (sc->argtypes[i] == ARG_FD) {
      printf("arg %d: ", i + 1);
      if ((int)args[i] == AT_FDCWD)
        printf("AT_FDCWD");
      else
        printf("%d", (int)args[i]);
    } else if (sc->argtypes[i] == ARG_HEX) {
      printf("arg %d: %llx", i + 1, args[i]);
    } else if (sc->argtypes[i] == ARG_FLAGS) {
      printf("arg %d: ", i + 1);
      print_open_flags(args[i]);
    } else if (sc->argtypes[i] == ARG_OCT) {
      printf("arg %d: 0%llo", i + 1, args[i]);
    } else if (sc->argtypes[i] == ARG_STR) {
      printf("arg %d: ", i + 1);
      char buf[256];
      if (args[i] == 0)
        printf("NULL");
      else if (read_string(child, args[i], buf, sizeof(buf)) < 0)
        printf("0x%llx", args[i]); /* bad pointer: show the raw address */
      else
        printf("\"%s\"", buf);
    }
    printf("\n");
  }
}
