#ifndef LOGIC_H
#define LOGIC_H

typedef struct {
    int **board;     
    int size;        
    int score;        
    int is_game_over; 
} GameState;


GameState* init_game(int size);  
void free_game(GameState *game);

void add_random_tile(GameState *game);
int move_left(GameState *game);
void rotate_board(GameState *game);
int move_right(GameState *game);
int move_up(GameState *game);
int move_down(GameState *game);

#endif