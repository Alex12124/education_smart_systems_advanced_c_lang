#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    float* arr;
    int cap;
    int sz;
} float_vector;


void init_vector(float_vector* v, int sz) {
    if (sz < 0)
    {
        return;
    }
    
    if (sz == 0)
    {
        v->arr = NULL;
        v->cap = 0;
        v->sz = 0;
        return;
    }
    v->arr = malloc(sizeof(float) * sz);
    for (int i = 0; i < sz; i++)
    {
        v->arr[i] = 0;
    }
    v->cap = sz;
    v->sz = sz;
}

int push_back_vector(float_vector* v, int val) {

    if (v->cap == 0)
    {
        float* new_arr = malloc(sizeof(float));
        if (new_arr == NULL)
        {
            return -1;
        }
        v->cap = 1;
        v->sz = 1;
        v->arr = new_arr;
        v->arr[0] = val;
        return 1;
    }
    
    if (v->cap == v->sz)
    {
        float* new_arr = malloc(sizeof(float) * v->cap * 2);
        if (new_arr == NULL)
        {
            return 0;
        }
        v->cap *= 2;
        memcpy(new_arr, v->arr, v->sz * sizeof(float));
        free(v->arr);
        v->arr = new_arr;
        v->arr[v->sz] = val;
        v->sz++;
    } else
    {
        v->arr[v->sz] = val;
        v->sz++;
    }
    return 1;
}

void pop_back_vector(float_vector* v)
{
    if (v == NULL || v->arr == NULL || v->sz == 0)
    {
        return;
    }
    v->sz--;
}


void destroy_vector(float_vector* v)
{
    if (v != NULL && v->arr != NULL)
    {
        free(v->arr);
        v->cap = 0;
        v->sz = 0;
    }
}

int is_digit(char c)
{
    return '0' <= c && c <= '9';
}

float do_operation(float a, float b, char operation)
{
    switch (operation)
    {
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
    case '+':
        return a + b;
    case '-':
        return a - b;
    default:
        return 0;
    }
}

int get_number(char* arr, int sz)
{
    int res = 0;
    for (int i = 0; i < sz; i++)
    {
        res = res * 10 + (arr[i] - '0');
    }
    return res;
}

int main()
{
    float_vector v;
    char number_str[10] = {0};
    unsigned char utf8_symbol[2] = {0};
    int utf8_symbol_sz = 0;
    int number_sz = 0;
    init_vector(&v, 0);
    for (int c = getchar(); c != '.'; c = getchar())
    {
        if (is_digit(c))
        {
            number_str[number_sz++] = c;
        } else if (c == ' ')
        {
            if (number_sz != 0)
            {
                push_back_vector(&v, get_number(number_str, number_sz));
            }
            number_str[0] = '\0';
            number_sz = 0;
        }
        else
        {
            if ((c & 0b11000000) == 0b11000000)
            {
                utf8_symbol[utf8_symbol_sz++] = c;
                continue;
            }
            utf8_symbol[utf8_symbol_sz++] = c;
            if ((utf8_symbol_sz == 2) && ((int) utf8_symbol[0] == 0xC3) 
                && (utf8_symbol[1] = 0x97))
            {
                c = '*';
            }
            
            float res = do_operation(v.arr[v.sz - 2], v.arr[v.sz - 1], c);
            utf8_symbol_sz = 0;
            pop_back_vector(&v);
            pop_back_vector(&v);
            push_back_vector(&v, res);
        }
    }
    printf("%d\n", (int)v.arr[0]);
    destroy_vector(&v);
    return 0;
}