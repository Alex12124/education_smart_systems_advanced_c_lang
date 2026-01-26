#pragma once

#include <stdint.h>
#include "point.h"
#include "point_vector.h"
#include "ncurses.h"


enum {LEFT = 1, UP, RIGHT, DOWN, STOP_GAME = KEY_F(10) };

typedef struct {
    int down;
    int up;
    int left;
    int right;
} control_buttons;



typedef struct {
    point_t point;
    int direction;
    point_vector tail;
    control_buttons controls;
} snake_t ;

void init_snake(snake_t* snake, int init_sz, int x, int y);
void destroy_snake(snake_t* snake);