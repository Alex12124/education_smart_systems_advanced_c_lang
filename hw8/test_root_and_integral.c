#include "root_and_integral.h"
#include "math_functions.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

// Тест сравнивает аналитическое решение корней с численным решением
// или решение с geogebra с численным решением
void test_root()
{
    const double EPSILON1 = 0.0001; // погрешность
    root_result res = root(f1, f3, -6, -4, EPSILON1, df1, df3, ddf1, ddf3);
    if (fabs(res.res - (-3 - sqrt(16.2)) / 1.2) > EPSILON1)
    {
        printf("test root failed\n");
        exit(1);
    }
    res = root(f1, f3, 0.1, 1, EPSILON1, df1, df3, ddf1, ddf3);
    if (fabs(res.res - (-3 + sqrt(16.2)) / 1.2) > EPSILON1)
    {
        printf("test root failed\n");
        exit(1);
    }
    res = root(f2, f3, -1, -0.1, EPSILON1, df2, df3, ddf2, ddf3);
    if (fabs(res.res - (-0.243928854)) > EPSILON1)
    {
        printf("test root failed\n");
        exit(1);
    }
    res = root(f2, f3, 2, 4, EPSILON1, df2, df3, ddf2, ddf3);
    if (fabs(res.res - (3.243928807)) > EPSILON1)
    {
        printf("test root failed\n");
        exit(1);
    }

    res = root(f1, f2, 2, 4, EPSILON1, df1, df2, ddf1, ddf2);
    if (fabs(res.res - (3.847760245)) > EPSILON1)
    {
        printf("test root failed\n");
        exit(1);
    }
    printf("test root is successeful\n");
}

// Тест сравнивает разность первообразных с численным решением интеграла
void test_integral()
{
    const double EPSILON2 = 0.00001; // погрешность
    double res = integral(f1, 0.5, 5, EPSILON2);
    if (fabs(res - (primitive_f1(5) - primitive_f1(0.5))) > EPSILON2)
    {
        printf("test integral failed\n");
        exit(1);
    }
    res = integral(f2, 0.5, 5, EPSILON2);
    if (fabs(res - (primitive_f2(5) - primitive_f2(0.5))) > EPSILON2)
    {
        printf("test integral failed\n");
        exit(1);
    }
    res = integral(f3, 0.5, 5, EPSILON2);
    if (fabs(res - (primitive_f3(5) - primitive_f3(0.5))) > EPSILON2)
    {
        printf("test integral failed\n");
        exit(1);
    }
    printf("test integral is successful\n");
}