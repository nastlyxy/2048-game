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