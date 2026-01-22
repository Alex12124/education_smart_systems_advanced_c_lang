#include <stdio.h>
#include <limits.h>

int main() {
    int n = 0;
    int maximum = INT_MIN;
    int count = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int number = 0;
        scanf("%d", &number);
        if (number > maximum)
        {
            maximum = number;
            count = 1;
        } else if (number == maximum)
        {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}
