# Compilador - ajuste conforme necessário
CC = gcc

# Nome do executável
TARGET = tabela_hash

SRCS = tabela_hash.c

CFLAGS = -Wall -Wextra -pedantic -std=c99

ifeq ($(OS),Windows_NT)
    TARGET := $(TARGET).exe

    CFLAGS += -D_CRT_SECURE_NO_WARNINGS
    
    RM = del /Q
else
    RM = rm -f
endif

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	$(RM) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run