#include <stdio.h>
#include <stdint.h>

int extractExp(float x)
{
    union floatbit
    {
        float f;
        struct
        {
            uint32_t mant: 23;
            uint32_t exp: 8;
            uint32_t sign: 1;
        } bit;
        
    } tmp;
    tmp.f = x;
    return tmp.bit.exp;
}


int main()
{
    float x;
    scanf("%f", &x);
    printf("%d\n", extractExp(x));
   
    return 0;
}
