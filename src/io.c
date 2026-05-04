#include <stdio.h>
#include <stdlib.h>
#include "io.h"

void save_game(GameState *game, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    fprintf(file, "%d %d %d\n", game->size, game->score, game->is_game_over);

    for (int i = 0; i < game->size; i++) {
        for (int j = 0; j < game->size; j++) {
            fprintf(file, "%d ", game->board[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

GameState* load_game(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    int size, score, is_game_over;
    if (fscanf(file, "%d %d %d", &size, &score, &is_game_over) != 3) {
        fclose(file);
        return NULL;
    }

    GameState *game = init_game(size);
    game->score = score;
    game->is_game_over = is_game_over;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fscanf(file, "%d", &game->board[i][j]);
        }
    }

    fclose(file);
    return game;
}