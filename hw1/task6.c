#include <stdio.h>

int main() {
    unsigned n;
    scanf("%u", &n);
    printf("%u\n", n ^ 0xFF000000);
    return 0;
}