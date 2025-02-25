CC = g++

CFLAGS = -std=c++11 -Wall

# Nome do arquivo fonte e do executável
SRC = main.cpp
OUT = lista_encadeada

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	del /F $(OUT).exe 2>nul || rm -f $(OUT)  