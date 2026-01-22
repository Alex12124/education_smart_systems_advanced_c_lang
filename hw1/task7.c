#include <stdio.h>

int main() {
    unsigned n;
    scanf("%u", &n);
    unsigned res = 0;
    for (int i = 0; i < n; i++)
    {
        unsigned number = 0;
        scanf("%u", &number);
        res ^= number;
    }
    printf("%u\n", res);

    return 0;
}