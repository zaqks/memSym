#include "lists.h"

typedef ListNode QueueNode;
typedef List Queue;

Queue *initQueue()
{
    return (Queue *)initList();
}

void pushQueueNode(Queue *lst, void *val)
{
    addListNode1(lst, val);
}

void *popQueueNode(Queue *lst)
{
    void *rslt = (void *)(lst->head->val);
    removeListNode(lst, 0);

    return rslt;
}

void printQueue(Queue *queue)
{
    char *seprator = "______________";
    printf("%s\n", seprator);
    //

    void *val;
    int len = queue->length;

    while (len > 0)
    {
        val = popQueueNode(queue);
        pushQueueNode(queue, val);
        printf("%p\n%s\n", val, seprator);
        len--;
    }
}
