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

#endif