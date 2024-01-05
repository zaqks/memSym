

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

void *popStackNode(Stack *stk)
{
    void *rslt = (void *)(stk->head->val);
    removeListNode(stk, 0);

    return rslt;
}

void printStack(Stack *stk)
{
    printf("__\n");
    //
    Stack *tmp = initStack();
    void *val;
    int len = stk->length;

    while (len > 0)
    {
        val = popStackNode(stk);
        pushStackNode(tmp, val);
        printf("%p\n__\n", val);
        len--;
    }
    // refill
    len = tmp->length;
    while (len > 0)
    {
        val = popStackNode(tmp);
        pushStackNode(stk, val);

        len--;
    }

    free(tmp);
}
