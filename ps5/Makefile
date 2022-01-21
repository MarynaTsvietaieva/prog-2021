CC = gcc
CFLAGS = -std=c11 -Wall -Werror
LDLIBS = -lm
OUTPUT = ps5

#targets
all: backpack.o command.o container.o game.o item.o parser.o room.o world.o main.o
	$(CC) $(CFLAGS) $(LDLIBS) backpack.o command.o container.o game.o item.o parser.o room.o world.o main.o -o $(OUTPUT)

backpack.o: backpack.c
	$(CC) $(CFLAGS) $(LDLIBS) -c backpack.c

command.o: command.c
	$(CC) $(CFLAGS) $(LDLIBS) -c command.c

container.o: container.c
	$(CC) $(CFLAGS) $(LDLIBS) -c container.c

game.o: game.c
	$(CC) $(CFLAGS) $(LDLIBS) -c game.c

item.o: item.c
	$(CC) $(CFLAGS) $(LDLIBS) -c item.c

parser.o: parser.c
	$(CC) $(CFLAGS) $(LDLIBS) -c parser.c

room.o: room.c
	$(CC) $(CFLAGS) $(LDLIBS) -c room.c

world.o: world.c
	$(CC) $(CFLAGS) $(LDLIBS) -c world.c

main.o: main.c
	$(CC) $(CFLAGS) $(LDLIBS) -c main.c

clean:
	$(RM) *.o $(OUTPUT)

