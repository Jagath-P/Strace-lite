#include "config.h"
#include <stddef.h>
#include <stdlib.h>
int read_string(pid_t child, unsigned long long addr, char *out, size_t size);
void start_trace(char *argv[], int pos, struct config *cfg);
// parses "trace=openat,read" specifically void
// parse_e_option(const char *optarg, trace_config_t *cfg);
