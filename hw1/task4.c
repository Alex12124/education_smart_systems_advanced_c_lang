#include <stdio.h>

int find_first_set_bit(unsigned n)
{
    for (int i = 31; i >= 0; i--)
    {
        if (n & (1 << i))
        {
            return i;
        }
    }
    return -1;
}

int power_int(int a, int b)
{
    int res = 1;
    for (int i = 0; i < b; i++)
    {
        res *= a;
    }
    return res;
}

int find_max_for_some_bits(unsigned n, int first_set_bit_pos, int count_of_bits)
{
    const unsigned window = power_int(2, count_of_bits) - 1;
    for (unsigned mask = power_int(2, count_of_bits) - 1; mask > 0; mask--)
    {
        for (int left_pos = first_set_bit_pos; left_pos + 1 >= count_of_bits; left_pos--)
        {
            if (((n >> (left_pos - count_of_bits + 1)) & mask) == mask)
            {
                return mask;
            }
        }
    }
    return 0;
    
}

int main() {
    unsigned n;
    unsigned k;
    scanf("%u %u", &n, &k);
    int pos = find_first_set_bit(n);
    int maximum = find_max_for_some_bits(n, pos, pos + 1 > k ? k: pos + 1);
    printf("%d\n", maximum);
    return 0;
}
