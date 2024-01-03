const int ramSize = 1024; // 1KB

typedef struct
{
    int freeSpace; // for partitions
    List *partitions;
} Ram;

Ram *initRam()
{
    Ram *ram = (Ram *)malloc(sizeof(Ram));
    ram->freeSpace = ramSize;
    ram->partitions = initList();

    // create the partitions
    Partition *partition;
    for (int i = 0; i < 4; i++)
    {
        partition = initPartition(ramSize / 4);
        addListNode1(ram->partitions, partition);
        ram->freeSpace -= ramSize / 4;
    }

    return ram;
}

int loadProcess(Ram *ram, Process *process, int strategy)
{

    switch (strategy)
    {
    case 0: // first fit

        ListNode *current = ram->partitions->head;
        Partition *crntPart;
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
                    int remaining = crntPart->size - process->size;
                    if (remaining > 0)
                    {
                        crntPart->size = process->size;

                        crntPart = initPartition(remaining);
                        addListNode1(ram->partitions, crntPart);
                    }

                    return 1;
                }
            }
            current = current->next;
        }

        break;
    case 1: // best fit

        break;
    case 2: // worst fit

        break;
    default:
        break;
    }

    return 0;
}

void tickRam(Ram *ram)
{
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
            currentProcess->clocks -= 1;
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
                // free partition
                if (!currentProcesses->length)
                {
                    currentPartition->occupied = false;
                }
            }
        }

        current = current->next;
    }
}

// merge only one
int mergePartitions(Ram *ram)
{
    // merge random with largest

    ListNode *current = ram->partitions->head;
    int currentIndx = 0;
    Partition *currentPartition;

    // get the largest partition
    Partition *largest;
    int largestIndx;

    while (current)
    {
        currentPartition = (Partition *)current->val;

        if (!currentPartition->occupied)
        {
            if (largest)
            {
                if (currentPartition->size > largest->size)
                {
                    largest = currentPartition;
                    largestIndx = currentIndx;
                }
            }
            else
            {
                // init
                largest = currentPartition;
                largestIndx = currentIndx;
            }
        }

        current = current->next;
        currentIndx++;
    }

    // merge the first
    current = ram->partitions->head;
    currentIndx = 0;

    while (current)
    {
        currentPartition = (Partition *)current->val;

        if (
            !currentPartition->occupied)
        {
            if (currentIndx != largestIndx)
            {

                // merge
                largest->size += currentPartition->size;
                removeListNode(ram->partitions, currentIndx);
                return 1;
            }
        }

        current = current->next;
        currentIndx++;
    }

    return 0;
}