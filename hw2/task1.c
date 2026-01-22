#include <stdio.h>

typedef struct list {
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

size_t totalMemoryUsage(list *head)
{
    size_t sum = 0;
    while (head)
    {
        sum += head->size;
        head = head->next;
    }
    return sum;
}

int main() {
   
    return 0;
}
