CC     = gcc
CFLAGS = -Wall -g
EXE    = main
OBJ    = main.o file_read.o fft.o

all: $(EXE)

$(EXE): $(OBJ)
		$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

file_read.o: file_read.h
		$(CC) $(CFLAGS) -c file_read.c

fft.o: fft.h
		$(CC) $(CFLAGS) -c fft.c

main.o: file_read.c file_read.h main.c fft.h fft.c
		$(CC) $(CFLAGS) -c main.c


clean:
		rm -f $(OBJ) $(EXE)