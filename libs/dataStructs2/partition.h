int partitionId = 0;

typedef struct partition
{
    int size;
    bool occupied;
    Array *startAdr;
    int id;
} Partition;

Partition *initPartition(int size)
{
    Partition *partition = (Partition *)malloc(sizeof(partition));
    partition->size = size;
    partition->occupied = false;
    partition->startAdr = initArray();

    partition->id = partitionId;
    partitionId += 1;

    return partition;
}

void pushProcess(Partition *partition, Process *process)
{
    pushArrayNode(partition->startAdr, process);
}

void printPartition(Partition *partition)
{
    printf("------partition %d------\n", partition->id);
    printf("size: %d Bytes\n\n", partition->size);
    

    Array *processes = partition->startAdr;
    Process *currentProcess;

    for (int i = 0; i < processes->length; i++)
    {
        currentProcess = (Process *)processes->arr[i].val;
        printProcess(currentProcess);
    }

    printf("-----------------------\n\n");
}