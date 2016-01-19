CC=gcc
CFLAGS=-Wall 
I=include
SRC=src
OBJ=obj
BIN=bin

all: ${BIN}/minMax ${BIN}/binarySearch

${BIN}/minMax: ${OBJ}/minMax.o 
	$(CC) -o $@ $^

${BIN}/binarySearch: ${OBJ}/binarySearch.o 
	$(CC) -o $@ $^

${OBJ}/minMax.o:${SRC}/minMax.c
	$(CC) -o $@ -c -O0 $< ${CFLAGS} -lrt

${OBJ}/binarySearch.o:${SRC}/binarySearch.c
	$(CC) -o $@ -c -O0 $< ${CFLAGS} -lrt

clean:
	rm -rf ${OBJ}/*.o ${BIN}/*
