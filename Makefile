CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = src/*.c main.c
TARGET = my_bc

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -rf $(TARGET)