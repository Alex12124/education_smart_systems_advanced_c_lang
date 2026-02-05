#include <stdio.h>
#include <string.h>

int get_number(char i, char j, char k)
{
    return (i - '0') * 100 + (j - '0') * 10 + (k - '0');
}

int main()
{
    char arr[1024] = {0};
    int numbers[1000] = {0};
    scanf("%1023s", arr);
    int len = strlen(arr);
    for (int i = 0; i < len - 2; i++)
    {
        for (int j = i + 1; j < len - 1; j++)
        {
            for (int k = j + 1; k < len; k++)
            {
                int number = get_number(arr[i], arr[j], arr[k]);
                numbers[number] = 1;
            }
        }
    }
    int sum = 0;
    for (int i = 100; i < 1000; i++)
    {
        sum += numbers[i];
    }
    printf("%d\n", sum);
    
    return 0;
}