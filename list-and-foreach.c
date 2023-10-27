/*Структура данных "двусвязный список"*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int Data;
struct Node
{
    struct Node *next;
    struct Node *prev;
    Data data;
};

// Без выделения и освобождения памяти:
void list_init(struct Node *list);                          // инициализация пустого списка.
void list_insert(struct Node *list, struct Node *t);        // вставляет элемент t после элемента list
void list_insert_before(struct Node *list, struct Node *t); // вставляет элемент t перед элементом list
void list_remove(struct Node *t);                           // удаляет элемент t из списка
// С выделением и освобождением памяти:
struct Node *list_push_front(struct Node *list, Data d); // выделяет память под новый элемент, содержащий данные d, и вставляет его в голову списка. Возвращает указатель на этот новый элемент или NULL, если произошла ошибка.
struct Node *list_push_back(struct Node *list, Data d);  // выделяет память под новый элемент, содержащий данные d, и вставляет его в хвост списка. Возвращает указатель на этот новый элемент или NULL, если произошла ошибка.
Data list_pop_front(struct Node *list);                  // удаляет голову списка, возвращает данные из удаленного узла.
Data list_pop_back(struct Node *list);                   // удаляет хвост списка, возвращает данные из удаленного узла.
Data list_delete(struct Node *t);                        // удаляет узел t из списка, возвращает данные из удаленного узла.
void list_clear(struct Node *list);                      // опустошает список, освобождая память. После этого можно опять добавлять элементы в список.
// Прочие функции:
void list_print(struct Node *list);   // распечатывает через пробел числа, лежащие в списке. С самого первого до последнего. В конце переводит строку. Полезна для отладки прочих функций.
int list_is_empty(struct Node *list); // проверяет пустой это список или нет
void test_non_alloc(int n);           // проверка без выделения памяти
void test_alloc(int n);               // проверка без с выделением памяти

int main(int argc, char *argv[])
{
    (void)argv;
    test_non_alloc(0);
    test_alloc(0);
    return 0;
}

// Прочие функции:
void list_foreach(struct Node *list, void (*func)(Data d, void *param),
                  void *param)
{
    struct Node *p;
    for (p = list->next; p != list; p = p->next)
        func(p->data, param);
}
void print_it(Data d, void *param)
{
    FILE *fd = param;
    fprintf(fd, "%d ", d);
}
void list_print(struct Node *list) // распечатывает через пробел числа, лежащие в списке. С самого первого до последнего. В конце переводит строку. Полезна для отладки прочих функций.
{
    /*for (struct Node *p = list->next; p != list; p = p->next)
    {
        printf("%d ", p->data);
    }
    printf("\n");*/
    list_foreach(list, print_it, stdout);
    printf("\n");
}
int list_is_empty(struct Node *list) // проверяет пустой это список или нет
{
    return list->next == list && list->prev == list;
}
// Без выделения и освобождения памяти:
void list_init(struct Node *list) // - инициализация пустого списка.
{
    list->next = list->prev = list;
}
void list_insert(struct Node *list, struct Node *t) // - вставляет элемент t после элемента list
{
    struct Node *q = list->next;
    t->prev = list;
    t->next = q;
    list->next = t;
    q->prev = t;
}
void list_insert_before(struct Node *list, struct Node *t) // - вставляет элемент t перед элементом list
{
    list_insert(list->prev, t);
}
void list_remove(struct Node *t) // - удаляет элемент t из списка
{
    struct Node *p = t->prev;
    struct Node *q = t->next;
    p->next = q;
    q->prev = p;
}
// С выделением и освобождением памяти:
struct Node *list_push_front(struct Node *list, Data d) // - выделяет память под новый элемент, содержащий данные d, и вставляет его в голову списка. Возвращает указатель на этот новый элемент или NULL, если произошла ошибка.
{
    struct Node *p = malloc(sizeof(struct Node));
    p->data = d;
    list_insert(list, p);
    return p;
}
struct Node *list_push_back(struct Node *list, Data d) // - выделяет память под новый элемент, содержащий данные d, и вставляет его в хвост списка. Возвращает указатель на этот новый элемент или NULL, если произошла ошибка.
{
    list_push_front(list->prev, d);
}
Data list_delete(struct Node *t) // - удаляет узел t из списка, возвращает данные из удаленного узла.
{
    Data res = t->data;
    list_remove(t);
    free(t);
    return res;
}
Data list_pop_front(struct Node *list) // - удаляет голову списка, возвращает данные из удаленного узла.
{
    return list_delete(list->next);
}
Data list_pop_back(struct Node *list) // - удаляет хвост списка, возвращает данные из удаленного узла.
{
    return list_delete(list->prev);
}
void list_clear(struct Node *list) // опустошает список, освобождая память. После этого можно опять добавлять элементы в список.
{
    while (!list_is_empty(list))
        list_pop_front(list);
}

void test_non_alloc(int n)
{
    struct Node *x = malloc(11 * sizeof(struct Node));
    struct Node *a = x + 10;

    list_init(a);
    assert(list_is_empty(a));
    if (n == 1)
        goto END;

    for (int i = 0; i < 10; i++)
    {
        x[i].data = i;
        list_insert(a, &x[i]);
    }
    list_print(a); // 9 8 7 6 5 4 3 2 1 0
    assert(!list_is_empty(a));
    if (n == 2)
        goto END;

    list_remove(&x[5]);
    list_print(a); // 9 8 7 6 4 3 2 1 0
    list_remove(&x[0]);
    list_print(a); // 9 8 7 6 4 3 2 1
    list_remove(&x[9]);
    list_print(a); // 8 7 6 4 3 2 1
    if (n == 3)
        goto END;

    list_insert_before(a, &x[0]);
    list_print(a); // 8 7 6 4 3 2 1 0
    list_insert(a, &x[9]);
    list_print(a); // 9 8 7 6 4 3 2 1 0
    list_insert(&x[6], &x[5]);
    list_print(a); // 9 8 7 6 5 4 3 2 1 0
    if (n == 4)
        goto END;

    while (!list_is_empty(a))
        list_remove(a->next);
    if (n == 5)
        goto END;

END:
    free(x);
}

void test_alloc(int n)
{
    struct Node a0, b0;
    struct Node *a = &a0;
    struct Node *b = &b0;

    list_init(a);
    list_init(b);

    int i;
    for (i = 0; i < 10; i++)
        list_push_back(a, i);
    list_print(a); // 0 1 2 3 4 5 6 7 8 9
    assert(list_is_empty(b));
    if (n == 6)
        goto END;

    for (i = 0; i < 10; i++)
        list_push_front(b, list_pop_back(a));
    list_print(b); // 0 1 2 3 4 5 6 7 8 9
    assert(list_is_empty(a));
    if (n == 7)
        goto END;

    for (i = 0; i < 10; i++)
    {
        list_push_front(a, i);
        list_pop_front(b);
    }
    list_print(a); // 9 8 7 6 5 4 3 2 1 0
    assert(list_is_empty(b));
    if (n == 8)
        goto END;

    for (i = 0; i < 10; i++)
        list_push_back(b, list_pop_front(a));
    list_print(b); // 9 8 7 6 5 4 3 2 1 0
    assert(list_is_empty(a));
    if (n == 9)
        goto END;

END:
    list_clear(a);
    list_clear(b);
}
