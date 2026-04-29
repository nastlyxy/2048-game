#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>   
#include "../include/logic.h" 

int main() {
    srand(time(NULL));

    GameState *game = init_game(4);

    add_random_tile(game);
    add_random_tile(game);

    printf("Starting board 2048:\n");
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
    printf("--------------------\n");

    free_game(game);

    return 0;
}