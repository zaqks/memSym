#include <stdlib.h>
#include <stdio.h>

typedef struct listNode
{
    void *val;
    struct listNode *next;
} ListNode;

typedef struct
{
    ListNode *head;
} List;

List *initList()
{
    List *lst = (List *)malloc(sizeof(List));
    lst->head = NULL;
}

int getListLength(List *lst)
{
    int length = 0;
    ListNode *current = lst->head;
    while (current)
    {
        length++;
        current = current->next;
    }

    return length;
}

ListNode *getListQueue(List *lst)
{
    ListNode *current = lst->head;
    while (current)
    {
        if (current->next)
        {
            current = current->next;
        }
        else
        {
            return current;
        }
    }
}

// queue mode
void addListNode1(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = NULL;

    if (!lst->head)
    {
        lst->head = newElem;
    }
    else
    {
        // find the last one
        ListNode *current = lst->head;
        getListQueue(lst)->next = newElem;
    }
}
// stack mode
void addListNode2(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = lst->head;

    lst->head = newElem;
}

int removeListNode(List *lst, int indx)
{
    if (indx < getListLength(lst))
    {
        ListNode *before = NULL;
        ListNode *current = lst->head;
        for (int i = 0; i < indx; i++)
        {
            before = current;
            current = current->next;
        }
        //
        // i = 0 whdha
        if (!indx)
        {
            lst->head = current->next;
        }
        // i = len - 1 whda

        //
        if (before)
        {
            before->next = current->next;
        }
        free(current);
        return 1;
    }
    printf("invalid indx\n");
    return 0;
}

void printList(List *lst)
{
    printf("[");
    ListNode *current = lst->head;
    while (current)
    {
        void *val = (void *)current->val;
        printf("%p ", val);
        current = current->next;
    }
    printf("]");
}
