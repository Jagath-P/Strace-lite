#include "include/api.h"
#include "include/config.h"
#include "include/syscall.h"
#include <linux/ptrace.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/user.h> // struct user_regs_struct
#include <sys/wait.h>
#include <unistd.h>

void start_trace(char *argv[], int pos, struct config *cfg) {
  pid_t child = fork();
  int status;
  if (child == 0) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    raise(SIGSTOP);
    execvp(argv[pos], argv + pos);
  } else {

    waitpid(child, &status, 0);

    ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);
    ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    int curr = 0;
    while (1) {
      waitpid(child, &status, NULL);
      if (WIFEXITED(status) || WIFSIGNALED(status)) {
        break;
      }

      if (!(WIFSTOPPED(status) && WSTOPSIG(status) == (SIGTRAP | 0x80))) {
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        continue;
      }
      struct ptrace_syscall_info info;

      long ret = ptrace(PTRACE_GET_SYSCALL_INFO, child, sizeof(info), &info);

      if (info.op == PTRACE_SYSCALL_INFO_ENTRY) {
        char buf[40];
        curr = info.entry.nr;
        if (cfg->filter[curr] != true) {
          ptrace(PTRACE_SYSCALL, child, NULL, NULL);
          continue;
        }
        printf("syscall : %llu\n", info.entry.nr);
      } else if (info.op == PTRACE_SYSCALL_INFO_EXIT) {
        if (cfg->filter[curr] != true) {
          ptrace(PTRACE_SYSCALL, child, NULL, NULL);
          continue;
        }
        printf("return value for syscall no: %d is %lld\n", curr,
               info.exit.rval);
      } else if (info.op == PTRACE_SYSCALL_INFO_NONE)
        break;
      ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
  }
}
