#include "include/api.h"
#include "include/config.h"
#include "include/syscall.h"
#include <stdio.h>
#include <string.h>

struct options Tropt = {0};

int extract_strings(char *s, struct config *cfg) {
  char *x = strtok(s, ",");
  if (!x)
    return -1;
  while (x) {
    struct syscall_def *sc = find_syscall_by_name(x);
    if (!sc) {
      return -2;
    }
    long num = sc->nr;
    cfg->filter[num] = true;
    x = strtok(NULL, ",");
  }

  return 0;
}

int parse_args(int argc, char *argv[], struct config *cfg) {
  int i = 1;
  while (i < argc) {
    printf("arg %d\n", i);
    char *s = argv[i];
    if (!strcmp(s, "-e")) {
      cfg->filter_enabled = true;
      if (i + 1 >= argc)
        return -1; // Missing filter

      if (extract_strings(argv[i + 1], cfg) < 0)
        return -2; // Invalid filter

      i += 2;
      continue;
    } else if (!strcmp(s, "-c")) {
      cfg->summary = true;

    } else if (!strcmp(s, "-T")) {
      cfg->timing = true;

    } else if (!strcmp(s, "-J")) {
      cfg->show_files = true;
    } else {
      return i;
    }
    i++;
  }

  return -1;
}
