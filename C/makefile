CC=gcc
CFLAGS=-Wall -ansi
I=include
SRC=src
OBJ=obj
BIN=bin

all: ${BIN}/minMax

${BIN}/minMax: ${OBJ}/minMax.o 
	$(CC) -o $@ $^

${OBJ}/minMax.o:${SRC}/minMax.c
	$(CC) -o $@ -c $< ${CFLAGS}

clean:
	rm -rf ${OBJ}/*.o ${BIN}/*
