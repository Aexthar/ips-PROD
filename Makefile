CC = g++
CFLAGS = -Wall -O3
CXXTESTINCLUDE = ./include/cxxTest/
ARMAINCLUDE = ./include/armadillo-lib/include
ARMALIB = ./include/armadillo-lib/lib
OPENBLASLIB = ./include/OpenBLAS-lib/lib
CXXTESTBIN = ./include/cxxTest/bin
SRC = ./dev/src
HDR = ./dev/hdr
OBJ = ./obj
TST = ./test
TARGET = ./out/main
TARGTEST = ./out/tests
CMPLOBJ = $(CC) -c $(CFLAGS) $< -I $(ARMAINCLUDE) -o $@

tests: $(TARGTEST)

all: $(TARGET)

$(TARGET): $(OBJ)/main.o $(OBJ)/polynomials.o $(OBJ)/constants.o $(OBJ)/trunc.o $(OBJ)/basis.o $(OBJ)/rho.o $(OBJ)/utils.o
	$(CC) -L$(ARMALIB) -larmadillo $^ -o $@

$(OBJ)/main.o: $(SRC)/main.cpp $(OBJ)/polynomials.o $(OBJ)/constants.o $(OBJ)/trunc.o $(OBJ)/basis.o $(OBJ)/rho.o $(OBJ)/utils.o
	$(CMPLOBJ)

$(OBJ)/rho.o : $(SRC)/rho.cpp $(HDR)/rho.h $(OBJ)/basis.o
	$(CMPLOBJ)

$(OBJ)/basis.o : $(SRC)/basis.cpp $(HDR)/basis.h $(OBJ)/constants.o $(OBJ)/polynomials.o
	$(CMPLOBJ)

$(OBJ)/trunc.o: $(SRC)/trunc.cpp $(HDR)/trunc.h $(OBJ)/constants.o
	$(CMPLOBJ)

$(OBJ)/polynomials.o: $(SRC)/polynomials.cpp $(HDR)/polynomials.h $(OBJ)/constants.o
	$(CMPLOBJ)

$(OBJ)/utils.o: $(SRC)/utils.cpp $(HDR)/utils.h
	$(CMPLOBJ)

$(OBJ)/constants.o: $(SRC)/constants.cpp $(HDR)/constants.h
	$(CMPLOBJ)

$(TARGTEST): $(TST)/tests.cpp $(SRC)/constants.cpp $(SRC)/polynomials.cpp $(SRC)/trunc.cpp $(SRC)/basis.cpp
	$(CC) -I $(ARMAINCLUDE) -I $(CXXTESTINCLUDE) $^ -o $@

$(TST)/tests.cpp: $(TST)/testBasis.h $(TST)/testPolynomial.h $(TST)/testTrunc.h
	$(CXXTESTBIN)/cxxtestgen --error-printer $^ -o $@ 

.PHONY: all clean tests

init:
	export LD_LIBRARY_PATH=$(ARMALIB):$(OPENBLASLIB)
	if [ ! -d ./out ]; then \
		mkdir ./out; \
	fi
	if [ ! -d $(OBJ) ]; then \
		mkdir $(OBJ); \
	fi

clean: 
	rm -f $(OBJ)/*.o
	rm -f out/*
	rm -f visu.png
	rm -f $(TST)/tests.cpp

visu:
	povray +A0.0001 -W800 -H600 +P +Q11 visu.pov