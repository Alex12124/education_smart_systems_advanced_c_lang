#include <stdio.h>

int count_set_bits(unsigned n)
{
    int res = 0;
    for (int i = 0; i < 32; i++)
    {
        if (n & (1 << i))
        {
            res++;
        }
    }
    return res;
}

int main() {
    unsigned n;
    scanf("%u", &n);
    printf("%d\n", count_set_bits(n));
    return 0;
}
