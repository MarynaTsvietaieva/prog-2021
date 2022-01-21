CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
OUTPUT=ps1

all: $(OUTPUT)

$(OUTPUT): playfair.o bmp.o main.o
		cppcheck --enable=performance, unusedFunction --error-exitcode=1 *.c
		gcc $(CFLAGS) playfair.o bmp.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
		gcc $(CFLAGS) -c main.c -o main.o

playfair.o: playfair.c playfair.h
		gcc $(CFLAGS) -c playfair.c -o playfair.o

bmp.o: bmp.c bmp.h
		gcc $(CFLAGS) -c bmp.c -o bmp.o

clean:
		rm -rf $(OUTPUT) *.o
