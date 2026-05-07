#include <stdlib.h>
#include "logic.h"

GameState* init_game(int size) {
    GameState *game = (GameState*)malloc(sizeof(GameState));
    if (game == NULL) return NULL; 
    
    game->size = size;
    game->score = 0;
    game->is_game_over = 0;

    game->board = (int**)malloc(size * sizeof(int*));
    if (game->board == NULL) {
        free(game);
        return NULL;
    }
    
    for (int i = 0; i < size; i++) {
        game->board[i] = (int*)malloc(size * sizeof(int));
        if (game->board[i] == NULL) {
            for (int k = 0; k < i; k++) free(game->board[k]);
            free(game->board);
            free(game);
            return NULL;
        }
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

int move_left(GameState *game) {
    int moved = 0;
    for (int i = 0; i < game->size; i++) {
        int target = 0;
        for (int j = 1; j < game->size; j++) {
            if (game->board[i][j] != 0) {
                int col = j;
                while (col > target && game->board[i][col - 1] == 0) {
                    game->board[i][col - 1] = game->board[i][col];
                    game->board[i][col] = 0;
                    col--;
                    moved = 1;
                }
                if (col > target && game->board[i][col - 1] == game->board[i][col]) {
                    game->board[i][col - 1] *= 2;
                    game->score += game->board[i][col - 1];
                    game->board[i][col] = 0;
                    target = col;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}

void rotate_board(GameState *game) {
    int temp[game->size][game->size];
    
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            temp[i][j] = game->board[i][j];
        }
    }
    
    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            game->board[j][game->size - 1 - i] = temp[i][j];
        }
    }
}

int move_right(GameState *game) {
    rotate_board(game);
    rotate_board(game);
    int moved = move_left(game);
    rotate_board(game);
    rotate_board(game);
    return moved;
}

int move_down(GameState *game) {
    rotate_board(game);
    int moved = move_left(game);
    rotate_board(game);
    rotate_board(game);
    rotate_board(game);
    return moved;
}

int move_up(GameState *game) {
    rotate_board(game);
    rotate_board(game);
    rotate_board(game);
    int moved = move_left(game);
    rotate_board(game);
    return moved;
}