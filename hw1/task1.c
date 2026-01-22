#include <stdio.h>

int is_lower_letter(char c)
{
    return 'a' <= c && c <= 'z';
}

int is_upper_letter(char c)
{
    return 'A' <= c && c <= 'Z';
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int first_symbol = 1;
    for (int c = getchar(); c != '.'; c = getchar())
    {
        if (is_lower_letter(c))
        {
            putchar((c - 'a' + n) % 26 + 'a');
        } else if (is_upper_letter(c))
        {
            putchar((c - 'A' + n) % 26 + 'A');
        }
        else if (c == ' ')
        {
            if (first_symbol)
            {
                first_symbol = 0;
                continue;
            }
            
            putchar(' ');
        }
    }
    printf(".\n");
    
    return 0;
}
