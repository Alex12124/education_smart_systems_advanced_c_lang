#include <stdio.h>
#include <stdint.h>

typedef struct list {
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

uint64_t findMaxBlock(list *head)
{
    size_t max_sz = 0;
    size_t res_address = 0;
    while (head)
    {
        if (head->size > max_sz)
        {
            max_sz = head->size;
            res_address = head->address;
        }
        head = head->next;
    }
    return res_address;
}
