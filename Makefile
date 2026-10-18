CC      := gcc
CFLAGS  := -Wall -Wextra -g 
TARGET  := tracer

all: $(TARGET)

$(TARGET): arg_parser.c main.c syscall_table.c tracer.c util.c ./include/api.h ./include/config.h ./include/syscall.h
	$(CC) $(CFLAGS) -o $@ arg_parser.c main.c syscall_table.c tracer.c util.c 

clean: 
	rm -f $(TARGET)

.PHONY: all clean asan



