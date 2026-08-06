#include <linux/ptrace.h>
#include <stddef.h>

#include "include/api.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

void read_string(pid_t child, unsigned long long addr, char *out, size_t buf) {
  size_t bytes_read = 0;
  while (bytes_read < buf - 1) {
    long word = ptrace(PTRACE_PEEKDATA, child, addr + bytes_read, NULL);
    if (word == -1) {
      break;
    }
    memcpy(out + bytes_read, &word, sizeof(long));
    for (size_t i = 0; i < sizeof(long); i++) {
      if (out[bytes_read + i] == '\0') {
        return; // done — string ends here
      }
    }
    bytes_read += sizeof(long);
  }
  out[buf - 1] = '\0'; // safety net if we hit bufsize without finding
}

char *cli_parser() {}
