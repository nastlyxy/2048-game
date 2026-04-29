#include <stdlib.h>
#include "logic.h"

GameState* init_game(int size) {
    GameState *game = (GameState*)malloc(sizeof(GameState));
    
    game->size = size;
    game->score = 0;
    game->is_game_over = 0;

    game->board = (int**)malloc(size * sizeof(int*));
    
    for (int i = 0; i < size; i++) {
        game->board[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            game->board[i][j] = 0; 
        }
    }

    return game;
}

void free_game(GameState *game) {
    if (game == NULL) return;
    for (int i = 0; i < game->size; i++) {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}

void add_random_tile(GameState *game) {
    int empty_cells[game->size * game->size][2]; 
    int empty_count = 0;

    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            if (game->board[i][j] == 0) {
                empty_cells[empty_count][0] = i; 
                empty_cells[empty_count][1] = j; 
                empty_count++;
            }
        }
    }

    if (empty_count == 0) return;

    int random_index = rand() % empty_count;
    int row = empty_cells[random_index][0];
    int col = empty_cells[random_index][1];

    game->board[row][col] = (rand() % 10 == 0) ? 4 : 2;
}