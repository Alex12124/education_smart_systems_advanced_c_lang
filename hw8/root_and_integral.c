#include "root_and_integral.h"
#include <math.h>


// комбинированный метод
root_result root(function f, function g, double a, double b, double eps1,
    function df, function dg, function ddf, function ddg)
{
    root_result res;
    int step_count = 0;

    while (fabs(a - b) > 2 * eps1)
    {
        double ya = f(a) - g(a);
        double yb = f(b) - g(b);
        double dya = df(a) - dg(a);
        double dyb = df(b) - dg(b);
        double ddya = ddf(a) - ddg(a);
        double ddyb = ddf(b) - ddg(b);
        if (ya * ddya < 0)
        {
            a = a - (ya * (a - b) / (ya - yb));
        } else
        {
            a = a - ya / dya;
        }
        if (yb * ddyb < 0)
        {
            b = b - (yb * (a - b) / (ya - yb));
        } else
        {
            b = b - yb / dyb;
        }
        step_count++;
    }
    res.res = (a + b) / 2;
    res.step_count = step_count;
    return res;
}

// Метод Симпсона
double integral(function f, double a, double b, double eps2)
{
    int n = 100; // Начальное количество разбиений (лучше четное)
    double sum = 0;
    double old_sum = 0;

    do {
        old_sum = sum;
        sum = 0;
        double h = (double)(b - a) / n;

        for (int i = 0; i < n; i++) {
            double x_left = a + i * h;
            double x_right = a + (i + 1) * h;
            double x_mid = a + (i + 0.5) * h;
            
            // Формула Симпсона для одного участка
            sum += (h / 6.0) * (f(x_left) + 4.0 * f(x_mid) + f(x_right));
        }

        n *= 2; // Удваиваем разбиение для проверки точности
        
        // Ограничитель, чтобы избежать бесконечного цикла
        if (n > 1000000) break; 

    } while (fabs(sum - old_sum) > eps2);
    return sum;
}