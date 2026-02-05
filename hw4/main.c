#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "snake.h"
#include <time.h>

int is_upper_symbol(char c)
{
    return ('A' <= c) && (c <= 'Z'); 
}

enum {
    MAX_FOOD_SIZE = 20, 
    SEED_NUMBER = 3,
    FOOD_EXPIRE_SECONDS = 10,
    STOP_GAME = KEY_F(10)
};

struct food
{
    int x;
    int y;
    time_t put_time;
    char point;
    uint8_t enable;
} food[MAX_FOOD_SIZE];

void init_food(struct food f[], size_t size)
{
    struct food init = {0,0,0,0,0};
    for(size_t i = 0; i < size; i++)
    {
        f[i] = init;
    }
}

void put_food_seed(struct food *fp)
{
    int max_x = 0; 
    int max_y = 0;
    char spoint[2] = {0};
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(fp->y, fp->x, " ");
    fp->x = rand() % (max_x - 1);
    fp->y = rand() % (max_y - 2) + 1;
    fp->put_time = time(NULL);
    fp->point = '$';
    fp->enable = 1;
    spoint[0] = fp->point;
    mvprintw(fp->y, fp->x, "%s", spoint);
}

void put_food(struct food f[], size_t number_seeds)
{
    for(size_t i = 0; i < number_seeds; i++)
    {
        put_food_seed(&f[i]);
    }
}

void refresh_food(struct food f[], int nfood)
{
    for(size_t i = 0; i < nfood; i++)
    {
        if(f[i].put_time)
        {
            if(!f[i].enable || (time(NULL) - f[i].put_time) > FOOD_EXPIRE_SECONDS)
            {
                put_food_seed(&f[i]);
            }
        }
    }
}

int check_collision(snake_t* snake)
{
    for (int i = 0; i < snake->tail.sz; i++)
    {
        if (snake->tail.arr[i].x == snake->point.x &&
            snake->tail.arr[i].y == snake->point.y)
        {
            return 1;
        }
    }
    return 0;
}

void consider_boundires(point_t* p)
{
    int max_x=0, max_y=0;
    getmaxyx(stdscr, max_y, max_x);
    if (p->x < 0)
    {
        p->x = max_x;
    }
    if (p->x > max_x)
    {
        p->x = 0;
    }
    if (p->y < 2)
    {
        p->y = max_y - 2;
    }
    if (p->y > max_y -2)
    {
        p->y = 2;
    }
}

void go(snake_t *head)
{
    char ch = '@';
    point_t new_point = head->point;
    switch (head->direction)
    {
        case LEFT:
            --new_point.x;
        break;
        case RIGHT:
            ++new_point.x;
            break;
        case UP:
            --new_point.y;
            break;
        case DOWN:
            ++new_point.y;
            break;
        default:
            break;
    }
    consider_boundires(&new_point);
    head->point = new_point;
    mvprintw(new_point.y, new_point.x, "%c", ch);
    refresh();
}

void go_tail(snake_t *head)
{
    char ch = '*';
    mvprintw(head->tail.arr[head->tail.sz - 1].y,
        head->tail.arr[head->tail.sz - 1].x, " ");
    for(size_t i = head->tail.sz - 1; i > 0; i--)
    {
        head->tail.arr[i] = head->tail.arr[i - 1];
        mvprintw(head->tail.arr[i].y, head->tail.arr[i].x, "%c", ch);
    }
    head->tail.arr[0] = head->point;
    mvprintw(head->tail.arr[0].y, head->tail.arr[0].x, "%c", ch);
}

void change_direction(snake_t* snake, const int32_t key)
{
    for (int i = 0; i < 2; i++)
    {
        control_buttons cb = default_controls[i];
        if (key == cb.down)
            snake->direction = DOWN;
        else if (key == cb.up)
            snake->direction = UP;
        else if (key == cb.right)
            snake->direction = RIGHT;
        else if (key == cb.left)
            snake->direction = LEFT;
    }
}

int check_direction(snake_t* snake, int32_t key)
{
    int old_direction = snake->direction;
    int new_direction;
    for (int i = 0; i < 2; i++)
    {
        control_buttons cb = default_controls[i];
        if (key == cb.down && old_direction == UP)
            return 0;
        else if (key == cb.up && old_direction == DOWN)
            return 0;
        else if (key == cb.right && old_direction == LEFT)
            return 0;
        else if (key == cb.left && old_direction == RIGHT)
            return 0;
    }
    return 1;
}

int main()
{
    snake_t snake; 
    init_snake(&snake, 5, 10, 10);
    int ch;
    initscr();
    keypad(stdscr, TRUE); 
    raw();
    noecho();
    curs_set(0);
    mvprintw(0, 1, "Use arrows for control. Press 'F10' for EXIT");
    timeout(0);
    init_food(food, MAX_FOOD_SIZE);
    put_food(food, SEED_NUMBER);
    int key_pressed = 0;
    while(key_pressed != STOP_GAME ) {
        key_pressed = getch();
        go_tail(&snake);
        go(&snake);
        if (check_collision(&snake))
        {
            mvprintw(1, 1, "Game over");
            timeout(5000);
            break;
        }
        
        timeout(100);
        refresh_food(food, SEED_NUMBER);
        if (is_upper_symbol(key_pressed))
        {
            key_pressed += 32;
        }
        if (check_direction(&snake, key_pressed))
        {
            change_direction(&snake, key_pressed);
        }
    }

    getch();
    endwin();
    destroy_snake(&snake);
    return 0;
}