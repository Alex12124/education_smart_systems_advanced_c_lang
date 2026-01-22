#include <stdio.h>

int main() {
    unsigned n;
    unsigned k;
    scanf("%u %u", &n, &k);
    printf("%u\n", n & (0xFFFFFFFF >> (32 - k)));
    return 0;
}
