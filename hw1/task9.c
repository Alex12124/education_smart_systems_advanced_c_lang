#include <stdio.h>
#include <stdint.h>

struct pack_array {
    uint32_t array; // поле для хранения упакованного массива из 0 и 1
    uint32_t count0 : 8; // счетчик нулей в array
    uint32_t count1 : 8; // счетчик единиц в array
};

void array2struct(int arr[], struct pack_array *pack)
{
    pack->array = 0;
    for (int i = 0; i < 32; i++)
    {
        if (arr[i] & 1)
        {
            pack->count1++;
            pack->array |= (1 << i);
        } else
        {
            pack->count0++;
        }
    }
}

void int_swap(int* a, int* b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void reverse_array(int arr[], int sz)
{
    for (int i = 0; i < sz / 2; i++)
    {
        int_swap(arr + i, arr + sz - i - 1);
    }
}

int main()
{
    int arr[32];
    for (int i = 0; i < 32; i++)
    {
        scanf("%d", arr + i);
    }
    reverse_array(arr, 32);
    struct pack_array p_arr;
    array2struct(arr, &p_arr);
    printf("%u %u %u\n", p_arr.array, p_arr.count0, p_arr.count1);
    return 0;
}
