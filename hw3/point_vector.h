#pragma once
#include "point.h"

typedef struct {
    point_t* arr;
    int cap;
    int sz;
} point_vector;

void init_point_vector(point_vector* v, int sz);
int push_back_point_vector(point_vector* v, point_t val);
void pop_back_point_vector(point_vector* v);
void destroy_point_vector(point_vector* v);
