#include <ncurses.h>
#include <unistd.h>
#include "snake.h"

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
    if (key == snake->controls.down)
        snake->direction = DOWN;
    else if (key == snake->controls.up)
        snake->direction = UP;
    else if (key == snake->controls.right)
        snake->direction = RIGHT;
    else if (key == snake->controls.left)
        snake->direction = LEFT;
}

int main()
{
    snake_t snake; 
    init_snake(&snake, 15, 10, 10);
    int ch;
    initscr();
    keypad(stdscr, TRUE); 
    raw();
    noecho();
    curs_set(0);
    mvprintw(0, 1, "Use arrows for control. Press 'F10' for EXIT");
    timeout(0);
    int key_pressed = 0;
    printw("Type text: \n");
    while(key_pressed != STOP_GAME ) {
        key_pressed = getch();
        go_tail(&snake);
        go(&snake);
        if (check_collision(&snake))
        {
            mvprintw(1, 1, "Game over");
            break;
        }
        
        timeout(100);
        change_direction(&snake, key_pressed);
    }
    timeout(5000);
    getch();
    endwin();
    destroy_snake(&snake);
    return 0;
}