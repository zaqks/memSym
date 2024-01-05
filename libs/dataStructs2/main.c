#define iStackLength 3
#define CLK 500

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "libs/lists.h"
#include "libs/stack.h"
#include "libs/queue.h"
#include "libs/arrays.h"
#include "libs/process.h"
#include "libs/partition.h"
#include "libs/ram.h"



int main()
{
    Queue *queue = initQueue();

    int *val;
    for (int i = 0; i < 10; i++)
    {
        val = (int *)malloc(sizeof(int));
        *val = i + 1;
        pushQueueNode(queue, val);
    }

    while (!emptyQueue(queue))
    {
        printf("%d\n", *((int *)popQueueNode(queue)));
    }

    return 1;
}