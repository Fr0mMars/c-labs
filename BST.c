#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef int Data;

struct Node
{
    Data val;
    struct Node *left;
    struct Node *right;
};

struct Node *tree_add(struct Node *tree, Data x)
{
    if (tree == NULL)
    {
        struct Node *p = malloc(sizeof(struct Node));
        p->val = x;
        p->left = p->right = NULL;
        return p;
    }
    if (x < tree->val)
        tree->left = tree_add(tree->left, x);
    if (x > tree->val)
        tree->right = tree_add(tree->right, x);
    return tree;
}

void tree_destroy(struct Node *tree)
{
    if (tree == NULL)
        return;
    tree_destroy(tree->left);
    tree_destroy(tree->right);
    free(tree);
    tree = NULL;
}

struct Node_of_queue
{
    struct Node_of_queue *next;
    struct Node_of_queue *prev;
    struct Node *data;
};

int list_is_empty(struct Node_of_queue *list)
{
    if (list->next == list && list->prev == list)
        return 1;
    return 0;
}

void list_init(struct Node_of_queue *list)
{
    list->next = list->prev = list;
}

void list_insert(struct Node_of_queue *list, struct Node_of_queue *t)
{
    struct Node_of_queue *q = list->next;
    t->prev = list;
    t->next = q;
    list->next = t;
    q->prev = t;
}
void list_insert_before(struct Node_of_queue *list, struct Node_of_queue *t)
{
    list_insert(list->prev, t);
}
void list_remove(struct Node_of_queue *t)
{
    struct Node_of_queue *p = t->prev;
    struct Node_of_queue *q = t->next;
    p->next = q;
    q->prev = p;
}

struct Node_of_queue *list_push_front(struct Node_of_queue *list, struct Node *d)
{
    struct Node_of_queue *p = malloc(sizeof(struct Node_of_queue));
    p->data = d;
    list_insert(list, p);
    return p;
}

struct Node_of_queue *list_push_back(struct Node_of_queue *list, struct Node *d)
{
    list_push_front(list->prev, d);
}

struct Node *list_delete(struct Node_of_queue *t)
{
    struct Node *res = t->data;
    list_remove(t);
    free(t);
    return res;
}

struct Node *list_pop_front(struct Node_of_queue *list)
{
    return list_delete(list->next);
}

void list_clear(struct Node_of_queue *list)
{
    while (list_is_empty(list) == 0)
        list_pop_front(list);
    free(list);
    list = NULL;
}

void list_print(struct Node_of_queue *list)
{
    for (struct Node_of_queue *p = list->next; p != list; p = p->next)
    {
        printf("%x ", p->data);
    }
    printf("\n");
}

void tree_print_wide(struct Node *tree)
{
    struct Node_of_queue *queue = malloc(sizeof(struct Node_of_queue));
    list_init(queue);
    list_push_back(queue, tree);
    //printf("tree after list_push_front = %x\n", tree);
    //list_print(queue);
    while (list_is_empty(queue) == 0)
    {
        struct Node *tmp = list_pop_front(queue);
        //printf("tmp after list_pop_front = %x\n", tmp);
        int res = tmp->val;
        printf("%d ", res);
        if (tmp->left != NULL)
        {
            list_push_back(queue, tmp->left);
        }
        if (tmp->right != NULL)
        {
            list_push_back(queue, tmp->right);
        }
    };
    list_clear(queue);
}

int main(void)
{
    struct Node *tree = NULL;
    int num;
    while (1)
    {
        scanf("%d", &num);
        if (num == 0)
            break;
        tree = tree_add(tree, num);
    };
    tree_print_wide(tree);
    tree_destroy(tree);
    return 0;
}
