#include "include/api.h"
#include "include/syscall.h"
#include <fcntl.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

struct syscall_def table[] = {
    {0, "read", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {1, "write", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {2, "open", 3, 0, {ARG_STR, ARG_HEX, ARG_OCT}},
    {3, "close", 1, 0, {ARG_FD}},
    {4, "stat", 2, 0, {ARG_STR, ARG_HEX}},
    {5, "fstat", 2, 0, {ARG_FD, ARG_HEX}},
    {6, "lstat", 2, 0, {ARG_STR, ARG_HEX}},
    {7, "poll", 3, 0, {ARG_HEX, ARG_INT, ARG_INT}},
    {8, "lseek", 3, 0, {ARG_FD, ARG_INT, ARG_INT}},
    {9, "mmap", 6, 0, {ARG_HEX, ARG_INT, ARG_HEX, ARG_HEX, ARG_FD, ARG_HEX}},
    {10, "mprotect", 3, 0, {ARG_HEX, ARG_INT, ARG_HEX}},
    {11, "munmap", 2, 0, {ARG_HEX, ARG_INT}},
    {12, "brk", 1, 0, {ARG_HEX}},
    {13, "rt_sigaction", 4, 0, {ARG_INT, ARG_HEX, ARG_HEX, ARG_INT}},
    {14, "rt_sigprocmask", 4, 0, {ARG_INT, ARG_HEX, ARG_HEX, ARG_INT}},
    {15, "rt_sigreturn", 0, 0, {0}},
    {16, "ioctl", 3, 0, {ARG_FD, ARG_HEX, ARG_HEX}},
    {17, "pread64", 4, 0, {ARG_FD, ARG_HEX, ARG_INT, ARG_INT}},
    {18, "pwrite64", 4, 0, {ARG_FD, ARG_HEX, ARG_INT, ARG_INT}},
    {19, "readv", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {20, "writev", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {21, "access", 2, 0, {ARG_STR, ARG_OCT}},
    {22, "pipe", 1, 0, {ARG_HEX}},
    {23, "select", 5, 0, {ARG_INT, ARG_HEX, ARG_HEX, ARG_HEX, ARG_HEX}},
    {24, "sched_yield", 0, 0, {0}},
    {25, "mremap", 5, 0, {ARG_HEX, ARG_INT, ARG_INT, ARG_HEX, ARG_HEX}},
    {28, "madvise", 3, 0, {ARG_HEX, ARG_INT, ARG_INT}},
    {32, "dup", 1, 0, {ARG_FD}},
    {33, "dup2", 2, 0, {ARG_FD, ARG_FD}},
    {35, "nanosleep", 2, 0, {ARG_HEX, ARG_HEX}},
    {39, "getpid", 0, 0, {0}},
    {41, "socket", 3, 0, {ARG_INT, ARG_HEX, ARG_INT}},
    {42, "connect", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {43, "accept", 3, 0, {ARG_FD, ARG_HEX, ARG_HEX}},
    {44, "sendto", 6, 0, {ARG_FD, ARG_HEX, ARG_INT, ARG_HEX, ARG_HEX, ARG_INT}},
    {45,
     "recvfrom",
     6,
     0,
     {ARG_FD, ARG_HEX, ARG_INT, ARG_HEX, ARG_HEX, ARG_HEX}},
    {49, "bind", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {50, "listen", 2, 0, {ARG_FD, ARG_INT}},
    {56, "clone", 5, 0, {ARG_HEX, ARG_HEX, ARG_HEX, ARG_HEX, ARG_HEX}},
    {57, "fork", 0, 0, {0}},
    {58, "vfork", 0, 0, {0}},
    {59, "execve", 3, 0, {ARG_STR, ARG_HEX, ARG_HEX}},
    {60, "exit", 1, 0, {ARG_INT}},
    {61, "wait4", 4, 0, {ARG_INT, ARG_HEX, ARG_HEX, ARG_HEX}},
    {62, "kill", 2, 0, {ARG_INT, ARG_INT}},
    {63, "uname", 1, 0, {ARG_HEX}},
    {72, "fcntl", 3, 0, {ARG_FD, ARG_INT, ARG_HEX}},
    {78, "getdents", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {79, "getcwd", 2, 0, {ARG_HEX, ARG_INT}},
    {80, "chdir", 1, 0, {ARG_STR}},
    {82, "rename", 2, 0, {ARG_STR, ARG_STR}},
    {83, "mkdir", 2, 0, {ARG_STR, ARG_OCT}},
    {84, "rmdir", 1, 0, {ARG_STR}},
    {87, "unlink", 1, 0, {ARG_STR}},
    {89, "readlink", 3, 0, {ARG_STR, ARG_HEX, ARG_INT}},
    {90, "chmod", 2, 0, {ARG_STR, ARG_OCT}},
    {96, "gettimeofday", 2, 0, {ARG_HEX, ARG_HEX}},
    {102, "getuid", 0, 0, {0}},
    {104, "getgid", 0, 0, {0}},
    {107, "geteuid", 0, 0, {0}},
    {108, "getegid", 0, 0, {0}},
    {110, "getppid", 0, 0, {0}},
    {158, "arch_prctl", 2, 0, {ARG_HEX, ARG_HEX}},
    {186, "gettid", 0, 0, {0}},
    {202,
     "futex",
     6,
     0,
     {ARG_HEX, ARG_INT, ARG_INT, ARG_HEX, ARG_HEX, ARG_INT}},
    {217, "getdents64", 3, 0, {ARG_FD, ARG_HEX, ARG_INT}},
    {218, "set_tid_address", 1, 0, {ARG_HEX}},
    {228, "clock_gettime", 2, 0, {ARG_INT, ARG_HEX}},
    {231, "exit_group", 1, 0, {ARG_INT}},
    {232, "epoll_wait", 4, 0, {ARG_FD, ARG_HEX, ARG_INT, ARG_INT}},
    {233, "epoll_ctl", 4, 0, {ARG_FD, ARG_INT, ARG_FD, ARG_HEX}},
    {257, "openat", 4, 0, {ARG_FD, ARG_STR, ARG_FLAGS, ARG_OCT}},
    {258, "mkdirat", 3, 0, {ARG_FD, ARG_STR, ARG_OCT}},
    {262, "newfstatat", 4, 0, {ARG_FD, ARG_STR, ARG_HEX, ARG_HEX}},
    {263, "unlinkat", 3, 0, {ARG_FD, ARG_STR, ARG_HEX}},
    {267, "readlinkat", 4, 0, {ARG_FD, ARG_STR, ARG_HEX, ARG_INT}},
    {271, "ppoll", 5, 0, {ARG_HEX, ARG_INT, ARG_HEX, ARG_HEX, ARG_INT}},
    {273, "set_robust_list", 2, 0, {ARG_HEX, ARG_INT}},
    {281,
     "epoll_pwait",
     6,
     0,
     {ARG_FD, ARG_HEX, ARG_INT, ARG_INT, ARG_HEX, ARG_INT}},
    {291, "epoll_create1", 1, 0, {ARG_HEX}},
    {292, "dup3", 3, 0, {ARG_FD, ARG_FD, ARG_HEX}},
    {293, "pipe2", 2, 0, {ARG_HEX, ARG_HEX}},
    {302, "prlimit64", 4, 0, {ARG_INT, ARG_INT, ARG_HEX, ARG_HEX}},
    {318, "getrandom", 3, 0, {ARG_HEX, ARG_INT, ARG_HEX}},
    {332, "statx", 5, 0, {ARG_FD, ARG_STR, ARG_HEX, ARG_HEX, ARG_HEX}},
    {334, "rseq", 4, 0, {ARG_HEX, ARG_INT, ARG_HEX, ARG_HEX}},
    {435, "clone3", 2, 0, {ARG_HEX, ARG_INT}},
    {439, "faccessat2", 4, 0, {ARG_FD, ARG_STR, ARG_OCT, ARG_HEX}},
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
      printf("arg %d: 0x%llx", i + 1, args[i]);
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
