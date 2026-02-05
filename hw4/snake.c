#include "snake.h"
#include "point_vector.h"
#include "ncurses.h"

control_buttons default_controls[2] = {
    {KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT},
    {'s', 'w', 'a', 'd'}
};

void init_snake(snake_t* snake, int tail_sz, int x, int y)
{
    init_point_vector(&(snake->tail), tail_sz);
    snake->direction = RIGHT;
    snake->point.x = x;
    snake->point.y = y;
    snake->controls = default_controls[1];
}

void destroy_snake(snake_t* snake)
{
    if (snake != NULL)
    {
        destroy_point_vector(&(snake->tail));
    }
}
