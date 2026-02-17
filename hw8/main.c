#include <stdint.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "math_functions.h"
#include "root_and_integral.h"
#include "test_root_and_integral.h"

enum { ROOTS = 5 }; // количество пересечений тремя задаными функциями


void calculate_roots(root_result *results)
{
    const double EPSILON1 = 0.0001; // погрешность
    results[0] = root(f1, f3, -6, -4, EPSILON1, df1, df3, ddf1, ddf3);
    results[1] = root(f2, f3, -1, -0.1, EPSILON1, df2, df3, ddf2, ddf3);
    results[2] = root(f1, f3, 0.1, 1, EPSILON1, df1, df3, ddf1, ddf3);
    results[3] = root(f2, f3, 2, 4, EPSILON1, df2, df3, ddf2, ddf3);
    results[4] = root(f1, f2, 2, 4, EPSILON1, df1, df2, ddf1, ddf2);
}

void print_abscissas(root_result *results, int sz)
{
    printf("abscissas:\n");
    for (int i = 0; i < sz; i++)
    {
        printf("x = %lf\n", results[i].res);
    }
}

void print_iterations(root_result *results, int sz)
{
    printf("iterations:\n");
    for (int i = 0; i < sz; i++)
    {
        printf("steps = %d\n", results[i].step_count);
    }
}

void print_help()
{
     printf("Application for finding the intersection of mathematical\n"
        "functions, as well as for calculating the integral of mathematical\n"
        "functions.\n"
        "Available flags:\n"
        "    [--help -h, --abscissas -a, --iterations -i, --test -t]\n"
        "h - for print help\n"
        "a - for print abscissas of intersection of math functions\n"
        "i - for print number of iterations of calculating root\n"
        "t - for testing root and integral functions\n"
    );
}

void do_test()
{
    test_root();
    test_integral();
}

static void command_arguments_processing(int argc, char** argv)
{
    int res = 0;
    struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"abscissas", no_argument, 0, 'a'},
        {"iterations", no_argument, 0, 'i'},
        {"test", no_argument, 0, 't'}
    }; // опции командной строки

    root_result results[ROOTS];
    calculate_roots(results);
    
    while ((res = getopt_long(argc, argv, "hait", long_options, NULL)) != -1)
    {
        switch (res)
        {
            case 'h':
                print_help();
                exit(0);
            case 'a':
                print_abscissas(results, ROOTS);
                break;
            case 'i':
                print_iterations(results, ROOTS);
                break;
            case 't':
                do_test();
                break;
            case '?':
                exit(1);
        }
    }
}


int main(int argc, char** argv)
{
    command_arguments_processing(argc, argv); // обработка аргументов командной строки
    return 0;
}
