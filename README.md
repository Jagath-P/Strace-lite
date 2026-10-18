# Strace-lite

A Remake of classic Strace project with limited core functionalities

The following functionalities are available

- `./tracer cat main.c` will display all the syscalls involved with their arguments and return values

- `./tracer -c ls` will display a summary of all the syscalls involved.

-`./tracer -e openat,write,mmap cat tracer.c` will filter only mentioned syscalls after -e flag and displays them

- `./tracer -J firefox` will display all the files opened in the process of invoking the actual firefox binary file.

## Building the executable

- `make` use this command inside the root directory of this repository (i.e where Makefile is located)

- `make clean` use this to delete the executable and build again

## Limitations

- x86_64 Linux only
- Decodes arguments of most common syscalls, (remaining ones need to be added yet!)
- `-c` timings include the ptrace stop overhead and the actual kernel work
