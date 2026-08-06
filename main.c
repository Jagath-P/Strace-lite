#include "include/api.h"
#include "include/syscall_table.h"
#include <linux/ptrace.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/user.h> // struct user_regs_struct
#include <sys/wait.h>
#include <unistd.h>

void start_trace(char *argv[]) {
  pid_t child = fork();
  if (child == 0) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    execvp(argv[1], argv + 1);
  } else {
    int status;
    waitpid(child, &status, 0);
    ptrace(PTRACE_SETOPTIONS, child, 0, PTRACE_O_TRACESYSGOOD);
    ptrace(PTRACE_SYSCALL, child, 0, 0);
    while (1) {
      waitpid(child, &status, 0);
      if (WIFEXITED(status) || WIFSIGNALED(status))
        break;

      struct user_regs_struct regs;
      ptrace(PTRACE_GETREGS, child, NULL, &regs);
      struct ptrace_syscall_info info;

      long ret = ptrace(PTRACE_GET_SYSCALL_INFO, child, sizeof(info), &info);
      if (info.op == PTRACE_SYSCALL_INFO_NONE) {
        int sig = WSTOPSIG(status);
        printf("SIGNAL: %d\n", sig);
      }
      switch (info.op) {
      case PTRACE_SYSCALL_INFO_ENTRY:
        // info.entry.nr   = syscall number
        // info.entry.args[0..5] = the 6 syscall arguments, raw
        printf("syscall no: %lld\n", info.entry.nr);

        const struct syscall_def *sc = find_syscall(info.entry.nr);

        if (sc) {
          printf("syscall name: %s\n", sc->name);
          printf("arguments: %d\n", sc->nargs);
        }

        break;
      case PTRACE_SYSCALL_INFO_EXIT:
        // info.exit.rval = return value
        // info.exit.is_error = 1 if it was an error
        printf("The return value is %lld\n\n", info.exit.rval);
        break;
      case PTRACE_SYSCALL_INFO_NONE:
        // this stop wasn't a syscall stop at all — it's a signal (see below)

        break;
      }

      ptrace(PTRACE_SYSCALL, child, NULL, NULL); // resume
    }
  }
}
