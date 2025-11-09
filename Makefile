CC = g++
CFLAGS = -Wall -O3
ARMAINCLUDE = ./include/armadillo-lib/include
ARMALIB = ./include/armadillo-lib/lib
OPENBLASLIB = ./include/OpenBLAS-lib/lib
SRC = ./dev/src
HDR = ./dev/hdr
OBJ = ./dev/obj
TARGET = ./out/main

all: $(TARGET)

$(TARGET): $(OBJ)/main.o $(OBJ)/polynomials.o $(OBJ)/constants.o $(OBJ)/trunc.o $(OBJ)/basis.o
	$(CC) -L$(ARMALIB) -larmadillo $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp $(OBJ)/polynomials.o $(OBJ)/constants.o $(OBJ)/trunc.o $(OBJ)/basis.o
	$(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

$(OBJ)/basis.o : $(SRC)/basis.cpp $(HDR)/basis.h $(OBJ)/constants.o $(OBJ)/polynomials.o
	$(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

$(OBJ)/trunc.o: $(SRC)/trunc.cpp $(HDR)/trunc.h $(OBJ)/constants.o
	$(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

$(OBJ)/polynomials.o: $(SRC)/polynomials.cpp $(HDR)/polynomials.h $(OBJ)/constants.o
	$(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

$(OBJ)/constants.o: $(SRC)/constants.cpp $(HDR)/constants.h
	$(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

.PHONY: all clean

init:
	export LD_LIBRARY_PATH=$(ARMALIB):$(OPENBLASLIB)
	if [ ! -d ./dev/obj ]; then \
		mkdir ./dev/obj; \
	fi
	if [ ! -d ./out ]; then \
		mkdir ./out; \
	fi

clean: 
	rm -f $(OBJ)/*.o
	rm -f out/*

