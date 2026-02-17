#pragma once

typedef float (*function)(float);

typedef struct
{
    double res;
    int step_count;
} root_result; // структура для хранения результата функции root и количества итераций


root_result root(function f, function g, double a, double b, double eps1,
    function df, function dg, function ddf, function ddg);
// нахождения корня комбинированным методом

double integral(function f, double a, double b, double eps2);
// численный интеграл через метод Симпсона