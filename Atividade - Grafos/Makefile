CC = gcc
CFLAGS = -Wall -Wextra -g3 -std=c99
TARGET = grafos
SRC = main.c grafo.c
OBJ = $(SRC:.c=.o)

ifeq ($(OS),Windows_NT)
    RM = del /Q /F
    TARGET := $(TARGET).exe
    MKDIR = mkdir
else
    RM = rm -f
    MKDIR = mkdir -p
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(TARGET)

run: all
	$(TARGET)

.PHONY: all clean run