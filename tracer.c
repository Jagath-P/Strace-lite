#include "include/api.h"
#include "include/config.h"
#include "include/syscall.h"
#include <bits/time.h>
#include <linux/ptrace.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/user.h> // struct user_regs_struct
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

struct stats st[512] = {0};
void start_trace(char *argv[], int pos, struct config *cfg) {
  pid_t child = fork();
  int status;
  struct timespec ts;
  if (child == 0) {
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    raise(SIGSTOP);
    execvp(argv[pos], argv + pos);
  } else {

    waitpid(child, &status, 0);

    ptrace(PTRACE_SETOPTIONS, child, NULL, PTRACE_O_TRACESYSGOOD);
    ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    int curr = 0;
    long long entry_time = 0;
    while (1) {
      waitpid(child, &status, 0);
      if (WIFEXITED(status) || WIFSIGNALED(status)) {
        break;
      }

      // to filter the normal execve syscall sigtrap return which causes the
      // info.op to be PTRACE_SYSCALL_INFO_NONE and break
      if (!(WIFSTOPPED(status) && WSTOPSIG(status) == (SIGTRAP | 0x80))) {
        ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        continue;
      }
      struct ptrace_syscall_info info;

      long ret = ptrace(PTRACE_GET_SYSCALL_INFO, child, sizeof(info), &info);

      if (info.op == PTRACE_SYSCALL_INFO_ENTRY) {
        curr = info.entry.nr;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        entry_time = ts.tv_sec * 1000000000LL + ts.tv_nsec;

        if (cfg->show_files && curr == 257) {
          char buf[256];
          read_string(child, info.entry.args[1], buf, sizeof(buf));
          printf("%s\n", buf);
        }
        if ((cfg->filter_enabled && cfg->filter[curr] != true) ||
            cfg->summary || cfg->show_files) {
          ptrace(PTRACE_SYSCALL, child, NULL, NULL);
          continue;
        }
        printf("Syscall : %lld\n", info.entry.nr);

        print_args(info.entry.args, info.entry.nr, child);
      } else if (info.op == PTRACE_SYSCALL_INFO_EXIT) {
        clock_gettime(CLOCK_MONOTONIC, &ts);
        st[curr].ns += (ts.tv_sec * 1000000000LL + ts.tv_nsec - entry_time);
        st[curr].calls += 1;
        if (info.exit.is_error) {
          st[curr].errors += 1;
        }
        if ((cfg->filter_enabled && cfg->filter[curr] != true) ||
            cfg->summary || cfg->show_files) {
          ptrace(PTRACE_SYSCALL, child, NULL, NULL);
          continue;
        }

        printf("Return value for syscall no: %d is %lld\n\n", curr,
               info.exit.rval);
      } else if (info.op == PTRACE_SYSCALL_INFO_NONE)
        break;
      ptrace(PTRACE_SYSCALL, child, NULL, NULL);
    }
  }
}
