#include "lists.h"

typedef ListNode StackNode;
typedef List Stack;

Stack *initStack()
{
    return (Stack *)initList();
}

void pushStackNode(Stack *stk, void *val)
{
    addListNode2(stk, val);
}

int popStackNode(Stack *stk)
{
    int *rslt = (int *)(stk->head->val);
    removeListNode(stk, 0);

    return *rslt;
}

void printStack(Stack *stk)
{
    printf("__\n");
    //
    Stack *tmp = initStack();
    int *val;
    int len = stk->length;

    while (len > 0)
    {
        val = (int *)malloc(sizeof(int));
        *val = popStackNode(stk);
        pushStackNode(tmp, val);
        printf("%d\n__\n", *val);
        len--;
    }
    // refill
    len = tmp->length;
    while (len > 0)
    {
        val = (int *)malloc(sizeof(int));
        *val = popStackNode(tmp);
        pushStackNode(stk, val);

        len--;
    }

    free(tmp);
}
