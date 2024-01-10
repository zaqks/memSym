int ramSize = 1024; // 1KB

typedef struct
{
    // int freeSpace; // for partitions
    List *partitions;
} Ram;

Ram *initRam()
{
    Ram *ram = (Ram *)malloc(sizeof(Ram));
    // ram->freeSpace = ramSize;
    ram->partitions = initList();

    // create the partitions
    Partition *partition;
    int partitionsNum = randomNum(3, 7);
    int freeSpace = ramSize;
    for (int i = 0; i < partitionsNum; i++)
    {
        partition = initPartition(ramSize / partitionsNum);
        addListNode1(ram->partitions, partition);
        freeSpace -= ramSize / partitionsNum;
    }

    return ram;
}

int loadProcess(Ram *ram, Process *process, int strategy)
{
    ListNode *current;
    Partition *crntPart;

    int difference;

    switch (strategy)
    {
    case 0: // first fit
        current = ram->partitions->head;
        while (current)
        {
            crntPart = (Partition *)current->val;
            if (!crntPart->occupied)
            {
                if (crntPart->size >= process->size)
                {
                    pushArrayNode(crntPart->startAdr, process);
                    crntPart->occupied = true;

                    // create a new partition
                    difference = crntPart->size - process->size;
                    if (difference > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(difference);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }
            }
            current = current->next;
        }

        break;
    case 1: // best fit
        difference = 0;
        // get hte largest partition  first the init the difference with it
        current = ram->partitions->head;
        while (current)
        {
            crntPart = current->val;
            if (crntPart->size > difference)
            {
                difference = crntPart->size;
            }

            current = current->next;
        }

        // get the difference
        int bestIndx = -1;
        current = ram->partitions->head;
        for (int i = 0; i < getListLength(ram->partitions); i++)
        {
            crntPart = current->val;
            if (!crntPart->occupied)
            {
                if (crntPart->size - process->size < difference)
                {
                    difference = crntPart->size - process->size;
                    bestIndx = i;
                }
            }

            current = current->next;
        }

        // load the process
        if (bestIndx > -1) // something was found
        {
            current = ram->partitions->head;
            while (current)
            {
                crntPart = current->val;
                if (!bestIndx)
                {
                    // load
                    pushArrayNode(crntPart->startAdr, process);
                    crntPart->occupied = true;

                    // create a new partition

                    if (difference > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(difference);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }

                bestIndx -= 1;
                current = current->next;
            }
        }

        break;
    case 2: // worst fit
        difference = 0;
        int worstIndx = -1;

        // get the difference
        current = ram->partitions->head;
        for (int i = 0; i < getListLength(ram->partitions); i++)
        {
            crntPart = current->val;
            if (!crntPart->occupied)
            {
                if (crntPart->size - process->size > difference)
                {
                    difference = crntPart->size - process->size;
                    worstIndx = i;
                }
            }

            current = current->next;
        }

        // load the process
        if (worstIndx > -1) // something was found
        {
            current = ram->partitions->head;
            while (current)
            {
                crntPart = current->val;
                if (!worstIndx)
                {
                    // load
                    pushArrayNode(crntPart->startAdr, process);
                    crntPart->occupied = true;

                    // create a new partition

                    if (difference > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(difference);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }

                worstIndx -= 1;
                current = current->next;
            }
        }

        break;
    default:
        break;
    }

    return 0;
}

int tickRam(Ram *ram) // returns if something was deleted
{
    bool deleted = false;
    // tick processes
    ListNode *current = ram->partitions->head;
    Partition *currentPartition;
    Array *currentProcesses;
    Process *currentProcess;

    while (current)
    {
        currentPartition = (Partition *)current->val;
        currentProcesses = (Array *)currentPartition->startAdr;
        for (int i = 0; i < currentProcesses->length; i++)
        {
            currentProcess = (Process *)currentProcesses->arr[i].val;

            if (currentProcess->clocks > 0)
            {
                currentProcess->clocks -= 1;
                currentProcess->exeTime -= (float)CLK / 1000;
            }
        }

        current = current->next;
    }
    // delete completed processes
    current = ram->partitions->head;
    while (current)
    {
        currentPartition = (Partition *)current->val;
        currentProcesses = (Array *)currentPartition->startAdr;
        for (int i = 0; i < currentProcesses->length; i++)
        {
            currentProcess = (Process *)currentProcesses->arr[i].val;
            if (!currentProcess->clocks)
            {
                // delete the proces
                delArrayNode(currentProcesses, i);
                i -= 1;
                deleted = true;
                // free partition
                if (!currentProcesses->length)
                {
                    currentPartition->occupied = false;
                }
            }
        }

        current = current->next;
    }
    return deleted;
}

// merge randomly
int mergePartitions(Ram *ram) // returns  merged
{

    List *partitions = ram->partitions;
    ListNode *current = partitions->head;

    Partition *currentPartition;
    int freeNum = 0;

    // get freeNum
    while (current)
    {
        currentPartition = (Partition *)current->val;
        if (!currentPartition->occupied)
        {
            freeNum += 1;
        }

        current = current->next;
    }

    //
    current = partitions->head;

    Partition *toDel;
    int toDelIndx;

    if (freeNum > 1)
    {
        // get the one to free
        for (int i = 0; i < getListLength(ram->partitions); i++)
        {

            currentPartition = (Partition *)current->val;
            if (!currentPartition->occupied)
            {
                toDel = currentPartition;
                toDelIndx = i;
                break;
            }

            current = current->next;
        }

        // merge
        current = partitions->head;
        for (int i = 0; i < getListLength(ram->partitions); i++)
        {

            currentPartition = (Partition *)current->val;

            if (!currentPartition->occupied)
            {
                if (i != toDelIndx)
                {
                    // merge toDel with the current
                    currentPartition->size += toDel->size;
                    // delete to del
                    freeArray(toDel->startAdr);
                    removeListNode(partitions, toDelIndx);

                    // break;
                    return 1;
                }
            }

            current = current->next;
        }
    }
    return 0;
}

void printRam(Ram *ram)
{
    printf("__________RAM__________\n\n");

    ListNode *currentPart = ram->partitions->head;

    while (currentPart)
    {
        printPartition(currentPart->val);

        currentPart = currentPart->next;
    }

    printf("_______________________\n\n\n");
}

void printIQueue(Queue *queue)
{
    Process *current;
    for (int i = 0; i < queueLength(queue); i++)
    {
        current = popQueueNode(queue);
        pushQueueNode(queue, current);

        printProcess(current);
    }
}

void printIStack(Stack *stk)
{

    printf("________iSTACK_________\n\n");

    Stack *tmpStk = initStack();

    Queue *current;
    for (int i = 0; !emptyStack(stk); i++)
    {
        printf("--queue%d--------------\n", i);

        current = popStackNode(stk);
        pushStackNode(tmpStk, current);

        printIQueue(current);

        printf("----------------------\n");
    }

    while (!emptyStack(tmpStk))
    {
        pushStackNode(stk, popStackNode(tmpStk));
    }

    free(tmpStk);
    printf("_______________________\n\n\n");
}