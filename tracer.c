#include "include/api.h"
#include "include/flag_functions.h"
#include "include/syscall.h"
#include <stdio.h>

int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("Just nothing!, try using any of the functions of strace-lite\n");
    return 0;
  }

  int ret = parse_args(argc, argv);
  if (ret < 0) {
    printf("Incorrect format used!, Try again!!\n");
  }
  start_trace(argv, ret);
}
