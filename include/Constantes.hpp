#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP
// the size is adjustable, but the size must be even and grater than 3
#define SIZE 8
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY '-'
#define LEGAL '+'


// Define all the possible directions in which a player's move can flip
// their adversary's tiles as constant (0 – the current row/column,
// +1 – the next row/column, -1 – the previous row/column)
// left-up, up, right-up, left, right, left-down, down, right-down
const int DIRS[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

typedef enum
{
    HUMANO_VS_CPU = 1,
    HUMANO_VS_HUMANO,
    CPU_VS_CPU,
    LOAD_GAME
} GameMode; 


#endif