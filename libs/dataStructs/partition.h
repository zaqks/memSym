typedef struct partition
{
    int size;
    bool occupied;
    Process *startAdr;
} Partition;

Partition *initPartition(int size)
{
    Partition *partition = (Partition *)malloc(sizeof(partition));
    partition->size = size;
    partition->occupied = false;
    partition->startAdr = (Process *)calloc(size / sizeof(Process *), sizeof(Process *));

    return partition;
}