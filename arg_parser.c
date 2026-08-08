#include "include/api.h"
#include "include/syscall.h"
#include <stdio.h>
#include <string.h>

struct options Tropt = {0};

int e_flag_fmt(char *argv[], int *pos, int n) {
  if (*pos + 1 == n) {
    return -1;
  }

  (*pos)++;

  char *key = strtok(argv[*pos], "=");
  char *value = strtok(NULL, "=");

  char *sys = strtok(value, ",");
  while (sys != NULL) {
    struct syscall_def *t = find_syscall_by_name(sys);
    if (t) {
      //      printf("Setting trace_bit for syscall %s (nr=%ld)\n", t->name,
      //      t->nr);
      t->trace_bit = 1;
    }
    sys = strtok(NULL, ",");
  }
  return 0;
}

int parse_args(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    char *s = argv[i];
    if (!strcmp(s, "-e")) {
      Tropt.e_flag = 1;
      int ret = e_flag_fmt(argv, &i, argc);
      if (ret < 0)
        return -1;
    } else if (!strcmp(s, "-f")) {
      Tropt.f_flag = 1;
    }

    else
      return i;
  }

  return 0;
}
