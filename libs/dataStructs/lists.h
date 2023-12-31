#include <stdlib.h>
#include <stdio.h>

typedef struct listNode
{
    void *val;
    struct listNode *next;
} ListNode;

typedef struct
{
    int length;
    ListNode *head;
    ListNode *queue;
} List;

List *initList()
{
    List *lst = (List *)malloc(sizeof(List));
    lst->head = NULL;
    lst->length = 0;
}
//queue mode
void addListNode1(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = NULL;

    if (lst->length == 0)
    {
        lst->head = newElem;
    }
    else
    {
        lst->queue->next = newElem;
    }
    lst->queue = newElem;
    lst->length += 1;
}
//stack mode 
void addListNode2(List *lst, void *val)
{
    ListNode *newElem = (ListNode *)malloc(sizeof(ListNode));
    newElem->val = val;
    newElem->next = lst->head;

    lst->head = newElem;
    if (lst->length == 0)
    {
        lst->queue = newElem;
    }

    lst->length += 1;
}

void removeListNode(List *lst, int indx)
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
    if (indx == 0)
    {
        lst->head = current->next;
    }
    // i = len - 1 whda

    //
    if (before != NULL)
    {
        before->next = current->next;
        if(indx == lst->length -1){
            lst->queue = before;
        }
    }
    free(current);

    lst->length -= 1;
}

void printList(List *lst)
{
    printf("[");
    ListNode *current = lst->head;
    for (int i = 0; i < lst->length; i++)
    {
        int *val = (int *)current->val;
        printf("%d ", *val);
        current = current->next;
    }
    printf("]");
}
