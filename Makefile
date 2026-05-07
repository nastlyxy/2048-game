CC = gcc
CFLAGS = -Wall -Wextra -I./include
LDFLAGS = -lSDL2 -lSDL2_ttf

all: game

game: src/main.c src/logic.c src/io.c src/ui.c
	$(CC) $(CFLAGS) src/main.c src/logic.c src/io.c src/ui.c -o game $(LDFLAGS)

clean:
	rm -f game