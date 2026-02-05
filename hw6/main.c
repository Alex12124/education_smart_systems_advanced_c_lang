#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include "snake.h"
#include <time.h>

#define PLAYERS  2

int is_upper_symbol(char c)
{
    return ('A' <= c) && (c <= 'Z'); 
}

enum {
    START_TAIL_SIZE = 3,
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

int have_eat(snake_t *snake, struct food f[])
{
    for (int i = 0; i < SEED_NUMBER; i++)
    {
        if (f[i].x == snake->point.x &&
            f[i].y == snake->point.y)
        {
            return 1;
        }
    }
    return 0;
}

void repair_seed(struct food f[], size_t nfood, snake_t *snake)
{
    for(size_t i = 0; i < snake->tail.sz; i++)
        for(size_t j = 0; j < nfood; j++)
        {
            if (f[j].x == snake->tail.arr[i].x &&
                f[j].y == snake->tail.arr[i].y &&
                f[j].enable)
            {
                f[j].enable = 0;
                refresh_food(f, SEED_NUMBER);
            }
        }
    for(size_t i = 0; i < nfood; i++)
        for(size_t j = 0; j < nfood; j++)
        {
            if (i != j && f[i].enable &&
                f[j].enable && f[j].x == f[i].x &&
                f[j].y == f[i].y && f[i].enable)
            {
                f[i].enable = 0;
                f[j].enable = 0;
                refresh_food(f, SEED_NUMBER);
            }
        }
}

int is_crush(snake_t* snake)
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

void add_tail(snake_t *snake)
{
    point_t p;
    p.x = 0;
    p.y = 0;
    push_back_point_vector(&(snake->tail), p);
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

void update(snake_t *snake, struct food f[], const int32_t key)
{

    go_tail(snake);
    go(snake);
    if (check_direction(snake, key))
    {
        change_direction(snake, key);
    }
    refresh_food(food, SEED_NUMBER);
    if (have_eat(snake, food))
    {
        add_tail(snake);
    }
    refresh();
    timeout(80);
}

int main()
{
    snake_t snakes[PLAYERS];
    for (int i = 0; i < PLAYERS; i++)
        init_snake(snakes + i, START_TAIL_SIZE, 10 + i * 10,
            10 + i * 10);
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
        if (is_upper_symbol(key_pressed))
        {
            key_pressed += 32;
        }
        for (int i = 0; i < PLAYERS; i++)
        {
            update(snakes + i, food, key_pressed);
            if (is_crush(snakes + i))
            {
                mvprintw(1, 1, "Game over");
                timeout(5000);
                break;
            }
            repair_seed(food, SEED_NUMBER, snakes + i);
        }
        
    }

    getch();
    endwin();
    for (int i = 0; i < PLAYERS; i++)
        destroy_snake(snakes + i);
    return 0;
}