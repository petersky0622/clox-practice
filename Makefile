CC ?= gcc
CFLAGS ?= -std=c99 -Wall -Wextra -pedantic -I.
LDFLAGS ?=

TARGET := clox
SRCS := chunk.c compiler.c debug.c main.c memory.c object.c scanner.c table.c value.c vm.c
OBJS := $(SRCS:.c=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: all
	./scripts/test_compiler.sh

clean:
	rm -f $(TARGET) $(OBJS)
