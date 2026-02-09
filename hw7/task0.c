#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    char word[20];
    struct node* next;
};

typedef struct
{
    struct node* head;      
} list;

void add_to_list(list* lst, char* word)
{
    struct node* new_node = malloc(sizeof(struct node));
    strcpy(new_node->word, word);
    new_node->next = lst->head;
    lst->head = new_node;
}

void swap_elements(struct node* lhs, struct node* rhs)
{
    char tmp_str[20];
    strcpy(tmp_str, lhs->word);
    strcpy(lhs->word, rhs->word);
    strcpy(rhs->word, tmp_str);
}

void print_list(list* lst)
{
    if (lst->head == NULL)
    {
        return;
    }
    
    struct node* tmp = lst->head;
    int first_el = 1;
    while (tmp)
    {
        if (first_el)
        {
            first_el = 0;
            printf("%s", tmp->word);
        } else
        {
            printf(" %s", tmp->word);
        }
        tmp = tmp->next;
    }
    printf("\n");
}

void delete_list(list* lst)
{
    struct node* tmp = lst->head;
    while (tmp)
    {
        struct node* delete_node = tmp;
        tmp = tmp->next;
        free(delete_node);
    }
    lst->head = NULL; 
}

void sort_list(list* lst)
{
    struct node* tmp = lst->head;
    while (tmp)
    {
        struct node* next_node = tmp->next;
        while (next_node)
        {
            if (strcmp(tmp->word, next_node->word) > 0)
            {
                swap_elements(tmp, next_node);
            }
            next_node = next_node->next;
        }
        tmp = tmp->next; 
    }
}


int main()
{
    list lst;
    lst.head = NULL;
    char word[20];
    int word_sz = 0;
    for (int c = getchar(); c != '.'; c = getchar())
    {
        if (c == ' ')
        {
            word[word_sz] = '\0';
            add_to_list(&lst, word);
            word[0] = '\0';
            word_sz = 0;
        } else {
            word[word_sz++] = c;
        }
    }
    word[word_sz] = '\0';
    add_to_list(&lst, word);
    sort_list(&lst);
    print_list(&lst);
    delete_list(&lst);
    return 0;
}