
// splits "openat,read,write" into individual syscall names
int split_string(char *str, char *out[], int max);

// looks up a syscall name -> number using your existing table
int syscall_name_to_nr(const char *name);

void read_string();
