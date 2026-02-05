#include "point_vector.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"

void init_point_vector(point_vector* v, int sz) {
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
    v->arr = malloc(sizeof(point_t) * sz);
    for (int i = 0; i < sz; i++)
    {
        v->arr[i].x = 0;
        v->arr[i].y = 0;
    }
    
    v->cap = sz;
    v->sz = sz;
}

int push_back_point_vector(point_vector* v, point_t val) {

    if (v->cap == 0)
    {
        point_t* new_arr = malloc(sizeof(point_t));
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
        point_t* new_arr = malloc(sizeof(point_t) * v->cap * 2);
        if (new_arr == NULL)
        {
            return 0;
        }
        v->cap *= 2;
        memcpy(new_arr, v->arr, v->sz * sizeof(point_t));
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

void pop_back_point_vector(point_vector* v)
{
    if (v == NULL || v->arr == NULL || v->sz == 0)
    {
        return;
    }
    v->sz--;
}


void destroy_point_vector(point_vector* v)
{
    if (v != NULL && v->arr != NULL)
    {
        free(v->arr);
        v->cap = 0;
        v->sz = 0;
    }
}
