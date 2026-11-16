CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11 -D_POSIX_C_SOURCE=200809L -g -fsanitize=address,undefined
LDFLAGS = -fsanitize=address,undefined

SRC = src/shell.c src/parser.c src/executor.c src/builtins.c
OBJ = $(SRC:.c=.o)
TARGET = mish

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
