# Strace-lite

A minimalist debugging,diagnostic utility for Linux. It helps you observe how user level program interacts with the operating system.

The following functionalities are available

- `./tracer cat main.c` will display all the syscalls involved with their arguments and return values

- `./tracer -c ls` will display a summary of all the syscalls involved.

- `./tracer -e openat,write,mmap cat tracer.c` will filter only mentioned syscalls after -e flag and displays them

- `./tracer -J firefox` will display all the files opened in the process of invoking the actual firefox binary file.

- <img width="2522" height="1143" alt="Screenshot from 2026-10-18 10-50-19" src="https://github.com/user-attachments/assets/66aadf1a-e41c-4a5b-b65f-b18e385a1b65" />

## Building the executable

- `make` use this command inside the root directory of this repository (i.e where Makefile is located)

- `make clean` use this to delete the executable and build again

## Limitations

- x86_64 Linux only
- Decodes arguments of most common syscalls, (remaining ones need to be added yet!)
- `-c` timings include the ptrace stop overhead and the actual kernel work

## Further

- `-o` flag to redirect output to a file
- display signal info
- `-p` attach tracer to already existing process
- syscall injection feature to modify the arguments of syscalls

## Acknowledgements

Inspired by strace. This project explores what can be traced from user space
with ptrace, and where the limits of that approach are.
