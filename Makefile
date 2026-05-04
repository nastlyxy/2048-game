CC = gcc
CFLAGS = -Wall -Wextra -I./include

all: game

game: src/main.c src/logic.c src/io.c
	$(CC) $(CFLAGS) src/main.c src/logic.c src/io.c -o game

clean:
	rm -f game