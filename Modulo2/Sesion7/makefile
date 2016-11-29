SRC = src
INC =
OBJ =
BIN = bin
LIB =

all: $(BIN)/servidor $(BIN)/clientes $(BIN)/proxy

$(BIN)/servidor: $(SRC)/servidor.c
	gcc -o $(BIN)/servidor $(SRC)/servidor.c

$(BIN)/clientes: $(SRC)/clientes.c
	gcc -o $(BIN)/clientes $(SRC)/clientes.c

$(BIN)/proxy: $(SRC)/proxy.c
	gcc -o $(BIN)/proxy $(SRC)/proxy.c

clear:
	rm bin/*
