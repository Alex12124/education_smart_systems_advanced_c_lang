#include <stdio.h>

int abs_int(int a)
{
    return a > 0 ? a : -a;
}

int get_rest_weight(int weight, int* count)
{
    int sum_weight = 0;
    int i = 0;
    for (int kettlebell = 1; kettlebell < 1000000; kettlebell *= 3)
    {
        i++;
        sum_weight += kettlebell;
        if (kettlebell == weight)
        {
            (*count)++;
            return 0;
        } else if (sum_weight > weight)
        {
            (*count)++;
            return abs_int(kettlebell - weight);
        } else if (sum_weight == weight)
        {
            (*count) += i;
            return 0;
        }
    }
    return -1;
}

void func(int weight)
{
    int res = 0;
    do
    {
        weight = get_rest_weight(weight, &res);
        if (weight == -1)
        {
            printf("%d\n", -1);
            return;
        }
        
    } while (weight > 0);
    printf("%d\n", res);
}

int main()
{
    int weight;
    scanf("%d", &weight);
    func(weight);
    return 0;
}
