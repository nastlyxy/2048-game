CC = gcc
CFLAGS = -Wall -Wextra -I./include

all: game

game: src/main.c src/logic.c
	$(CC) $(CFLAGS) src/main.c src/logic.c -o game

clean:
	rm -f game