CC = g++
CFLAGS = -std=c++11 -Wall

# Nome do arquivo fonte e do executável
SRC = FilaSeq.cpp
OUT = fila

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)  # Remove o executável (compatível com Linux e macOS)

distclean: clean
