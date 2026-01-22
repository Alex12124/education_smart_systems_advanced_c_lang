#include <stdio.h>

unsigned right_rotate(unsigned n, unsigned k)
{
    return (n >> k) | ( n << (32 - k));
}

int main() {
    unsigned n;
    unsigned k;
    scanf("%u %u", &n, &k);
    printf("%u\n", right_rotate(n, k));
    return 0;
}
