typedef struct partition
{
    int size;
    bool occupied;
    Array *startAdr;
} Partition;

Partition *initPartition(int size)
{
    Partition *partition = (Partition *)malloc(sizeof(partition));
    partition->size = size;
    partition->occupied = false;
    partition->startAdr = initArray();

    return partition;
}

void pushProcess(Partition *partition, Process *process)
{
    pushArrayNode(partition->startAdr, process);
}