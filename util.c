#include "include/api.h"
#include <errno.h>
// #include <linux/ptrace.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int read_string(pid_t child, unsigned long long addr, char *out, size_t size) {
  size_t n = 0;
  while (n < size - 1) {
    errno = 0;
    long word = ptrace(PTRACE_PEEKDATA, child, addr + n, NULL);

    if (errno != 0) {
      if (n == 0)
        return -1; /* couldn't read anything */
      break;
    }
    char *p = (char *)&word;
    for (size_t i = 0; i < sizeof(long) && n < size - 1; i++) {
      out[n] = p[i];
      if (p[i] == '\0')
        return 0;
      n++;
    }
  }
  out[n] = '\0';
  return 0;
}
