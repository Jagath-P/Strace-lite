#include "include/api.h"
#include "include/config.h"
#include "include/syscall.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("Just nothing!, try using any of the functions of strace-lite\n");
    return 0;
  }
  struct config cfg = {0};

  int ret = parse_args(argc, argv, &cfg);
  if (ret == -1) {
    printf("No filter mentioned! Try again \n");
    exit(0);
  } else if (ret == -2) {
    start_trace(argv, 3, &cfg);
  } else
    start_trace(argv, ret, &cfg);

  if (cfg.summary) {
    printf("\n%-16s %8s %8s %12s\n", "syscall", "calls", "errors", "time (ms)");
    for (int i = 0; i < 512; i++) {
      if (st[i].calls == 0)
        continue;
      const struct syscall_def *sc = find_syscall(i);
      printf("%-16s %8d %8d %12.3f\n", sc ? sc->name : "?", st[i].calls,
             st[i].errors, st[i].ns / 1e6);
    }
  }
}
