#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include <stdint.h>
struct config {
  bool filter[512];
  bool summary;
  bool only_failures;
  bool show_files;
  bool filter_enabled;
  bool timing;
};
int parse_args(int argc, char *argv[], struct config *cfg);

#endif
