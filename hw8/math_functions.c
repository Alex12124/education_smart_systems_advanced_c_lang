#include "math_functions.h"
#include <math.h>
// Реализация функций, которые даны в курсовой работе
// Также реализации первой и второй производных функций

float f1(float x)
{
    return 0.6 * x + 3;
}

float primitive_f1(float x)
{
    return 0.3 * x * x + 3 * x;
}

float df1(float x)
{
    return 0.6;
}

float ddf1(float x)
{
    return 0;
}

float f2(float x)
{
    x -= 2;
    return x * x * x - 1;
}

float primitive_f2(float x)
{
    return 0.25 * pow(x, 4) - 2 * pow(x, 3) + 6 * pow(x, 2) - 9 * x;
}


float df2(float x)
{
    x -= 2;
    return 3 * x * x;
}

float ddf2(float x)
{
    x -= 2;
    return 6 * x;
}

float f3(float x)
{
    return 3 / x;
}

float primitive_f3(float x)
{
    return 3 * log(x);
}

float df3(float x)
{
    return -3 / (x * x);
}

float ddf3(float x)
{
    return 6 / (x * x * x);
}