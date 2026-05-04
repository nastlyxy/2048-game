#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/logic.h"

void print_board(GameState *game) {
    printf("--------------------\n");
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            if (game->board[i][j] == 0) {
                printf("   . ");
            } else {
                printf("%4d ", game->board[i][j]);
            }
        }
        printf("\n\n");
    }
    printf("Score: %d\n", game->score);
    printf("--------------------\n");
}

int main() {
    srand(time(NULL));
    GameState *game = init_game(4);

    add_random_tile(game);
    add_random_tile(game);

    printf("Init:\n");
    print_board(game);

    if (move_left(game)) {
        add_random_tile(game);
    }

    printf("After move_left:\n");
    print_board(game);

    free_game(game);
    return 0;
}