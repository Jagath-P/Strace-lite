// tracer.c — intercepts every syscall made by "ls"
#include <linux/ptrace.h>
#include <stddef.h>
#include <string.h>
#define _GNU_SOURCE
#include <stdio.h>
// #include <sys/ptrace.h>
#include "include/api.h"
#include "include/flag_functions.h"
#include "include/syscall_table.h"
#include <sys/user.h> // struct user_regs_struct
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("Just nothing!, try using any of the functions of strace-lite\n");
    return 0;
  }

  start_trace(argv);
}
