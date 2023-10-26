/*Стек на основе односвязного списка, тип struct Node *
Реализуйте структуру данных "односвязный список". Для этого при объявленных структурах Node (один элемент списка)*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int Data;
struct Node
{
    Data val;          // данные, которые хранятся в одном элементе
    struct Node *next; // указатель на следующий элемент списка
};

struct Node *list_create();
void list_push(struct Node **plist, Data x);
Data list_pop(struct Node **plist);
Data list_get(struct Node *list);
void list_print(struct Node *list);
int list_size(struct Node *list);
void list_clear(struct Node **plist);
int list_is_empty(struct Node *list);

void test0()
{
    struct Node *list = list_create();
    list_print(list);                               // пустая строка
    printf("is_empty = %d\n", list_is_empty(list)); // is_empty = 1
    printf("size = %d\n", list_size(list));         // size = 0

    list_push(&list, 21);
    list_print(list); // 21
    list_push(&list, 17);
    list_print(list); // 17 21
    list_push(&list, 3);
    list_print(list);                               // 3 17 21
    printf("is_empty = %d\n", list_is_empty(list)); // is_empty = 0
    printf("size = %d\n", list_size(list));         // size = 3

    Data x = list_pop(&list);
    printf("pop %d\n", x);                  // pop 3
    list_print(list);                       // 17 21
    printf("size = %d\n", list_size(list)); // size = 2

    list_clear(&list);
    list_print(list);                               // пустая строка
    printf("is_empty = %d\n", list_is_empty(list)); // is_empty = 1
    printf("size = %d\n", list_size(list));         // size = 0
}

int main(int argc, char *argv[])
{
    (void)argv;
    test0();
    return 0;
}

struct Node *list_create()
{
    return NULL;
}

void list_push(struct Node **plist, Data x)
{
    struct Node *p = malloc(sizeof(struct Node));
    p->val = x;
    p->next = *plist;
    *plist = p;
}

int list_is_empty(struct Node *list)
{
    int res = (list == NULL) ? 1 : 0;
    return res;
}

Data list_pop(struct Node **plist)
{
    if (list_is_empty(*plist) != 1)
    {
        struct Node *p = *plist;
        Data res = p->val;
        *plist = p->next;
        free(p);
        p = NULL;
        return res;
    }
    else
        printf("list_is_empty\n");
    // return NULL;
}

Data list_get(struct Node *list)
{

    if (list_is_empty(list) == 1)
    {
        printf("list_is_empty\n");
        // return NULL;
    }
    else
    {
        return list->val;
    }
}

void list_print(struct Node *list)
{

    /*for (struct Node * p = list; p != NULL; p = p->next) {
           printf("%d ", p->val);
       }
       printf("\n");*/
    struct Node *p = list;
    while (p != NULL)
    {
        printf("%d ", p->val);
        p = p->next;
    };
    printf("\n");
}

int list_size(struct Node *list)
{
    int i = 0;
    for (struct Node *p = list; p != NULL; p = p->next)
    {
        i++;
    }
    return i;
}

void list_clear(struct Node **plist)
{
    /*for (struct Node * p = *plist; p != NULL; p = *p->next) {
        list_pop(p);
    }*/
    while (list_is_empty(*plist) != 1)
    {
        list_pop(plist);
        /*struct Node * p = *plist;
        *plist = p->next;
        free(p);  */
    };
}
