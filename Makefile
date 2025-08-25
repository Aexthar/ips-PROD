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

$(TARGET): $(OBJ)/main.o $(OBJ)/solution-ho.o $(OBJ)/constants.o
	$(CC) -L$(ARMALIB) -larmadillo $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp $(OBJ)/solution-ho.o $(OBJ)/constants.o
	$(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

$(OBJ)/solution-ho.o: $(SRC)/solution-ho.cpp $(HDR)/solution-ho.h $(OBJ)/constants.o
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

